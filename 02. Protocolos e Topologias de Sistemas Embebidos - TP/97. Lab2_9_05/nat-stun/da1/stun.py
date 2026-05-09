import argparse
import asyncio
import os
import socket
import struct
import time

def ts():
    return f"{time.time():.6f}"

MAGIC_COOKIE = 0x2112A442

BINDING_REQUEST = 0x0001
BINDING_RESPONSE = 0x0101

ATTR_XOR_MAPPED_ADDRESS = 0x0020


# ---------------- STUN ----------------

def build_binding_request():
    txid = os.urandom(12)
    header = struct.pack("!HHI12s", BINDING_REQUEST, 0, MAGIC_COOKIE, txid)
    return header, txid


def parse_xor_mapped(value, txid):
    family = value[1]
    xport = struct.unpack("!H", value[2:4])[0]
    port = xport ^ (MAGIC_COOKIE >> 16)

    if family == 0x01:  # IPv4
        cookie_bytes = struct.pack("!I", MAGIC_COOKIE)
        raw_ip = bytes(a ^ b for a, b in zip(value[4:8], cookie_bytes))
        ip = socket.inet_ntoa(raw_ip)
        return ip, port

    raise ValueError("família não suportada")


def parse_stun(data, txid):
    msg_type, msg_len, cookie = struct.unpack("!HHI", data[:8])
    if cookie != MAGIC_COOKIE:
        raise ValueError("cookie inválido")

    if data[8:20] != txid:
        raise ValueError("txid inválido")

    attrs = data[20:20 + msg_len]
    pos = 0

    while pos + 4 <= len(attrs):
        atype, alen = struct.unpack("!HH", attrs[pos:pos + 4])
        value = attrs[pos + 4:pos + 4 + alen]

        if atype == ATTR_XOR_MAPPED_ADDRESS:
            return parse_xor_mapped(value, txid)

        pos += 4 + ((alen + 3) & ~3)

    raise RuntimeError("sem XOR-MAPPED-ADDRESS")


async def stun_query(sock, host, port):
    req, txid = build_binding_request()
    loop = asyncio.get_running_loop()

    await loop.sock_sendto(sock, req, (host, port))
    data, _ = await asyncio.wait_for(loop.sock_recvfrom(sock, 2048), 3)

    return parse_stun(data, txid)


# ---------------- MAIN ----------------

async def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--role", choices=["A", "B"], required=True)
    ap.add_argument("--local-port", type=int, required=True)
    ap.add_argument("--stun-host", required=True)
    ap.add_argument("--stun-port", type=int, default=3478)
    args = ap.parse_args()

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setblocking(False)
    sock.bind(("0.0.0.0", args.local_port))
    print(f"bind local port: {args.local_port}")
    print(f"[LOCAL] {sock.getsockname()}")

    # STUN
    print("[STUN] a obter endereço...")
    reflexive = await stun_query(sock, args.stun_host, args.stun_port)
    print(f"[STUN] reflexivo: {reflexive[0]}:{reflexive[1]}")

if __name__ == "__main__":
    asyncio.run(main())

