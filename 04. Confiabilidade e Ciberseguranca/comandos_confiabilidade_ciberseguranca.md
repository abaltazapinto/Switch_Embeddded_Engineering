Sim. Guarda isto como:

```text
comandos_confiabilidade_ciberseguranca.md
```

# Comandos essenciais — Confiabilidade e Cibersegurança

## 1. Rede Linux básica

```bash
ip a
ip -br a
```

Ver IPs e interfaces de rede.

```bash
ip route
```

Ver gateway/default route.

```bash
ping -c 4 8.8.8.8
```

Testar Internet por IP, sem depender de DNS.

```bash
ping -c 4 google.com
```

Testar Internet + DNS.

```bash
cat /etc/resolv.conf
```

Ver servidores DNS configurados.

```bash
getent hosts archive.ubuntu.com
```

Testar resolução DNS sem usar `ping`.

---

## 2. DNS

```bash
printf "nameserver 8.8.8.8\nnameserver 1.1.1.1\n" > /etc/resolv.conf
```

Corrigir DNS temporariamente.

```bash
dig google.com
dig @8.8.8.8 google.com
```

Testar resolução DNS e servidor DNS específico.

---

## 3. Serviços Linux

```bash
systemctl status <servico>
systemctl restart <servico>
systemctl enable <servico>
```

Ver, reiniciar e ativar serviços.

Exemplo:

```bash
systemctl status mosquitto
systemctl restart mosquitto
```

---

## 4. Portas abertas

```bash
ss -lntp
```

Ver portas TCP em escuta.

```bash
ss -lntp | grep 1883
ss -lntp | grep mosquitto
```

Ver se Mosquitto está a escutar em `1883` ou `8883`.

Interpretação:

```text
127.0.0.1:1883  → só local
0.0.0.0:1883    → acessível pela rede
0.0.0.0:8883    → MQTT TLS acessível pela rede
```

---

## 5. nmap

```bash
nmap <IP>
```

Scan básico.

```bash
nmap -Pn <IP>
```

Scan assumindo host ativo, mesmo sem ping.

```bash
nmap -p 22,80,1883,8883 <IP>
```

Testar portas específicas.

Interpretação:

```text
open      → serviço responde
closed    → host responde, mas porta fechada
filtered  → firewall bloqueia ou não responde
```

---

## 6. tcpdump

```bash
tcpdump -i any -nn
```

Capturar tráfego em todas as interfaces.

```bash
tcpdump -i any -nn 'tcp port 1883'
```

Ver MQTT sem TLS.

```bash
tcpdump -i any -nn 'tcp port 8883'
```

Ver MQTT com TLS.

```bash
tcpdump -i any -nn -c 20 'host 192.168.1.109 and tcp port 1883'
```

Capturar só 20 pacotes de um host.

```bash
tcpdump -i any -nn -w captura.pcap 'tcp port 1883'
```

Guardar captura para abrir no Wireshark.

```bash
tcpdump -nn -r captura.pcap | head -20
```

Ler ficheiro `.pcap` no terminal.

---

## 7. MQTT sem TLS

Broker local:

```bash
apt update
apt install -y mosquitto mosquitto-clients
systemctl status mosquitto
```

Cliente:

```bash
apt install -y mosquitto-clients
```

Subscriber:

```bash
mosquitto_sub -h 192.168.1.157 -t "isep/teste" -v
```

Publisher:

```bash
mosquitto_pub -h 192.168.1.157 -t "isep/teste" -m "ola mqtt"
```

Com debug:

```bash
mosquitto_pub -h 192.168.1.157 -t "isep/teste" -m "ola mqtt" -d
```

Linha importante:

```text
received CONNACK (0)
```

Significa que o broker aceitou a ligação.

---

## 8. MQTT remoto

```bash
getent hosts broker.hivemq.com
```

Testar DNS do broker remoto.

```bash
mosquitto_pub -h broker.hivemq.com -p 1883 -t "isep/teste" -m "teste remoto" -d
```

Testar MQTT remoto sem TLS.

Captura:

```bash
tcpdump -i any -nn 'host 192.168.1.109 and tcp port 1883'
```

---

## 9. MQTT com TLS

Broker a escutar em `8883`:

```bash
cat > /etc/mosquitto/conf.d/tls.conf <<'EOF'
listener 8883 0.0.0.0
cafile /etc/mosquitto/certs/ca.crt
certfile /etc/mosquitto/certs/server.crt
keyfile /etc/mosquitto/certs/server.key
allow_anonymous true
EOF
```

Reiniciar:

```bash
systemctl restart mosquitto
ss -lntp | grep mosquitto
```

Cliente com TLS:

```bash
echo "192.168.1.157 mqtt-broker" >> /etc/hosts
```

```bash
mosquitto_pub \
  -h mqtt-broker \
  -p 8883 \
  --cafile /root/ca.crt \
  -t "isep/teste" \
  -m "teste mqtt tls" \
  -d
```

Subscriber TLS:

```bash
mosquitto_sub \
  -h mqtt-broker \
  -p 8883 \
  --cafile /root/ca.crt \
  -t "isep/teste" \
  -v
```

---

## 10. Certificados TLS

Criar chave privada:

```bash
openssl genrsa -out ca.key 2048
```

Criar certificado CA:

```bash
openssl req -x509 -new -nodes -key ca.key -sha256 -days 365 -out ca.crt
```

Criar chave do servidor:

```bash
openssl genrsa -out server.key 2048
```

Criar CSR:

```bash
openssl req -new -key server.key -out server.csr
```

Assinar certificado do servidor:

```bash
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 365 -sha256
```

Permissões:

```bash
cp ca.crt server.crt server.key /etc/mosquitto/certs/

chown root:root /etc/mosquitto/certs/ca.crt /etc/mosquitto/certs/server.crt
chown mosquitto:mosquitto /etc/mosquitto/certs/server.key

chmod 644 /etc/mosquitto/certs/ca.crt /etc/mosquitto/certs/server.crt
chmod 640 /etc/mosquitto/certs/server.key
```

---

## 11. Proxmox / LXC

Entrar na shell do host Proxmox:

```bash
# pela interface: Node pve → Shell
```

Copiar ficheiro do container para o Proxmox:

```bash
pct pull 107 /etc/mosquitto/certs/ca.crt /root/ca.crt
```

Copiar ficheiro do Proxmox para outro container:

```bash
pct push 108 /root/ca.crt /root/ca.crt
```

Ver containers:

```bash
pct list
```

Entrar num container:

```bash
pct enter 108
```

---

## 12. Comandos de sobrevivência

```bash
apt update
apt install -y <pacote>
```

Instalar pacotes.

```bash
ls -lh
pwd
cat <ficheiro>
nano <ficheiro>
```

Navegação e edição básica.

```bash
find /root /etc/mosquitto -maxdepth 3 -type f
```

Encontrar ficheiros perdidos.

```bash
chmod 640 ficheiro
chown user:group ficheiro
```

Corrigir permissões.

---

# Comandos que deves mesmo decorar

```bash
ip -br a
ip route
ping -c 4 8.8.8.8
getent hosts google.com
systemctl status <servico>
ss -lntp
nmap -Pn <IP>
tcpdump -i any -nn 'tcp port <porta>'
mosquitto_pub -h <broker> -p <porta> -t "<topico>" -m "<mensagem>" -d
mosquitto_sub -h <broker> -p <porta> -t "<topico>" -v
```

# Frase mental

> Primeiro confirmo IP e rota. Depois DNS. Depois serviço ativo. Depois porta aberta. Depois tráfego com tcpdump. Depois interpreto em segurança.
