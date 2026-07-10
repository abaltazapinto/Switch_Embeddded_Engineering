## Sim — mas **não ligues tudo às cegas** ⚠️

Liga **só o necessário para demonstrar os guiões**, por ordem.

# Ação: ordem certa amanhã

## 1. Primeiro liga a OPNsense

No Proxmox, a OPNsense provavelmente é **VM**, não container.

```bash
qm list
qm start <ID-OPNsense>
```

Ou pela interface web: **Start** na VM da OPNsense.

### Objetivo

A firewall/router tem de estar ligada antes dos clientes, porque ela dá:

```text
gateway
DHCP
DNS
firewall rules
NAT
```

---

## 2. Depois liga os containers dos guiões

Ver containers:

```bash
pct list
```

Ligar container:

```bash
pct start <ID>
```

Entrar no container:

```bash
pct enter <ID>
```

---

# Ordem prática recomendada

```text
1. OPNsense
2. Ubuntu / Debian da LAN
3. Ubuntu / Debian da LAN2
4. Container/cliente da WAN
5. Broker MQTT, se estiver separado
```

---

# Antes de chamar o professor: valida isto ✅

Em cada container:

```bash
ip a
ip route
cat /etc/resolv.conf
```

Depois testa:

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

## Interpretação rápida

| Resultado                   | Significa                       |
| --------------------------- | ------------------------------- |
| `ping 8.8.8.8` dá           | IP/gateway/NAT provavelmente ok |
| `ping google.com` falha     | problema DNS                    |
| sem IP                      | DHCP/bridge errado              |
| sem default route           | gateway errado                  |
| não comunica entre LAN/LAN2 | regra firewall/routing          |

---

# Para mostrar Guião 4

Nos dois Ubuntu:

```bash
systemctl status apache2
ss -tulpn | grep :80
hostname -I
```

Testar de um para o outro:

```bash
curl http://<IP-do-outro>
```

ou:

```bash
wget http://<IP-do-outro>
```

Testar NAT pela WAN:

```bash
curl http://<IP-WAN-OPNsense>
```

---

# Para mostrar Guião 5 / “Wireshark”

Não precisas instalar Wireshark no container.

No Proxmox ou Linux onde passa o tráfego:

```bash
sudo tcpdump -i any port 1883
```

ou na bridge:

```bash
sudo tcpdump -i vmbr3 port 1883
sudo tcpdump -i vmbr4 port 1883
```

MQTT:

```bash
mosquitto_sub -h <IP-broker> -t teste
```

noutro terminal:

```bash
mosquitto_pub -h <IP-broker> -t teste -m "hello"
```

Para ver conteúdo em claro:

```bash
sudo tcpdump -i any -A port 1883
```

Para TLS:

```bash
sudo tcpdump -i any port 8883
```

---

# Frase que deves dizer se perguntarem

```text
Liguei primeiro a OPNsense porque ela é o gateway/firewall/DNS.
Depois liguei os clientes e servidores para confirmar IP, rota, DNS e serviços.
Para inspeção de tráfego, usei tcpdump na bridge/interface certa; não era obrigatório instalar Wireshark dentro dos containers.
```

---

# Pergunta de decisão

Amanhã, antes de mexeres nas regras, consegues identificar **qual container é LAN, qual é LAN2 e qual é WAN** só com `ip a` e `ip route`?
