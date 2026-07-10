## “+” — versão mais prática para mostrares ao professor ⚡

A lógica é: **comando → o que prova → como explicar**. Isto bate com o teu objetivo de estudo: não saber só executar, mas interpretar resultados, erros e segurança. 

---

# 0. Comandos universais — usar em todos os guiões

```bash
ip a
```

Ver IPs.

```bash
ip route
```

Ver gateway/default route.

```bash
cat /etc/resolv.conf
```

Ver DNS.

```bash
ping -c 4 <IP>
```

Testar conectividade IP.

```bash
ping -c 4 8.8.8.8
```

Testar saída para internet por IP.

```bash
ping -c 4 google.com
```

Testar internet + DNS.

```bash
dig google.com
```

Testar DNS.

```bash
ss -tulpn
```

Ver portas/serviços à escuta.

---

# Guião 1 — Proxmox, bridges, containers

## Mostrar IP e rede

```bash
ip a
ip route
```

## Testar internet

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

## Instalar ferramentas

```bash
sudo apt update
sudo apt install nmap apache2 openssh-server -y
```

## Testar Apache

```bash
systemctl status apache2
ss -tulpn | grep :80
curl localhost
```

## Testar bridge interna

```bash
ping -c 4 <IP-do-outro-container>
```

## SSH

```bash
ssh <user>@<IP-container>
```

## Chave SSH

```bash
ssh-keygen
ssh-copy-id <user>@<IP-container>
ssh <user>@<IP-container>
```

### Frase para dizer

```text
Neste guião provei que máquinas na mesma bridge comunicam diretamente.
Quando estão em bridges diferentes, precisam de router/firewall para comunicar.
```

---

# Guião 2 — OPNsense inicial + nmap

## Ver IPs nos containers

```bash
ip a
ip route
```

## Testar C2 para C3

```bash
ping -c 4 <IP-C3>
```

## Instalar nmap

```bash
sudo apt update
sudo apt install nmap -y
```

## Scan SYN

```bash
sudo nmap -sS -T4 <IP-C3>
```

## Scan ACK

```bash
sudo nmap -sA <IP-C3>
```

Atenção: se nas tuas notas apareceu isto:

```bash
nmap -sA -<IP-C3>
```

está errado. O correto é:

```bash
nmap -sA <IP-C3>
```

## Scan à firewall

```bash
sudo nmap -sS -T4 <IP-firewall>
sudo nmap -sA <IP-firewall>
```

### Interpretação

```text
open     = serviço acessível
closed   = host responde mas porta fechada
filtered = firewall bloqueia ou ignora
```

### Frase para dizer

```text
Com o nmap estou a testar a superfície exposta. Se aparece filtered, significa que a firewall não deixou obter resposta suficiente.
```

---

# Guião 3 — OPNsense Web + DHCP + DNS/Unbound

## Confirmar IP via DHCP

```bash
ip a
```

## Confirmar gateway

```bash
ip route
```

Esperado:

```text
default via 192.168.1.1
```

ou o IP LAN da tua OPNsense.

## Confirmar DNS

```bash
cat /etc/resolv.conf
```

Esperado:

```text
nameserver 192.168.1.1
```

## Testar internet

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

## Testar DNS

```bash
dig google.com
dig @192.168.1.1 google.com
```

## Aceder à OPNsense

No browser:

```text
https://192.168.1.1
```

ou o IP LAN que usaste.

### Diagnóstico rápido

```text
ping 8.8.8.8 funciona + ping google.com falha = DNS
ping tudo falha = gateway/firewall/rota
sem IP = DHCP
sem default route = gateway errado
```

### Frase para dizer

```text
Neste guião a OPNsense está a funcionar como gateway, DHCP server e DNS resolver da LAN.
```

---

# Guião 4 — Firewall rules + NAT + DNS forcing

Este é dos mais importantes.

## Ver IPs

```bash
ip a
hostname -I
ip route
cat /etc/resolv.conf
```

## Testar internet nos dois Ubuntu

```bash
ping -c 4 8.8.8.8
ping -c 4 google.com
```

## Instalar Apache nos dois

```bash
sudo apt update
sudo apt install apache2 -y
```

## Confirmar Apache

```bash
systemctl status apache2
ss -tulpn | grep :80
```

## Criar página clara para mostrar

No Ubuntu1:

```bash
echo "Pagina do Ubuntu1" | sudo tee /var/www/html/index.html
```

No Ubuntu2:

```bash
echo "Pagina do Ubuntu2" | sudo tee /var/www/html/index.html
```

## Testar HTTP entre redes

Do Ubuntu1 para Ubuntu2:

```bash
curl http://<IP-ubuntu2>
wget http://<IP-ubuntu2>
```

Do Ubuntu2 para Ubuntu1:

```bash
curl http://<IP-ubuntu1>
wget http://<IP-ubuntu1>
```

## Testar ping entre redes

```bash
ping -c 4 <IP-ubuntu1>
ping -c 4 <IP-ubuntu2>
```

## Testar NAT / port forward

A partir de um container na WAN:

```bash
curl http://<IP-WAN-OPNsense>
wget http://<IP-WAN-OPNsense>
```

Se abrir a página do Ubuntu interno:

```text
WAN → OPNsense WAN → NAT/Port Forward → Ubuntu interno
```

## Testar DNS forcing

```bash
dig google.com
dig @8.8.8.8 google.com
dig @1.1.1.1 google.com
```

Depois do forcing, a ideia é:

```text
mesmo que o cliente tente usar DNS externo, a firewall redireciona para o DNS interno/Unbound.
```

## Capturar DNS

```bash
sudo tcpdump -i any port 53
```

Na bridge do Proxmox:

```bash
sudo tcpdump -i vmbr3 port 53
sudo tcpdump -i vmbr4 port 53
```

### Frase para dizer

```text
Neste guião estou a aplicar o princípio do menor privilégio: só passa o tráfego explicitamente permitido por regras de firewall.
```

---

# Guião 5 — MQTT + Wireshark/tcpdump + TLS

## Instalar broker e clientes MQTT

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients -y
```

## Confirmar broker

```bash
systemctl status mosquitto
ss -tulpn | grep 1883
```

## Subscriber

```bash
mosquitto_sub -h <IP-broker> -t teste
```

## Publisher

```bash
mosquitto_pub -h <IP-broker> -t teste -m "hello"
```

Resultado esperado no subscriber:

```text
hello
```

## Broker remoto HiveMQ

Subscriber:

```bash
mosquitto_sub -h broker.hivemq.com -p 1883 -t teste/andre
```

Publisher:

```bash
mosquitto_pub -h broker.hivemq.com -p 1883 -t teste/andre -m "ola mqtt"
```

---

# Wireshark sem instalar Wireshark

Sim: podes dizer isto.

```text
Não instalei necessariamente Wireshark no container. Usei captura de tráfego com tcpdump ou packet capture na OPNsense/bridge e depois poderia abrir o .pcap no Wireshark.
```

## Capturar MQTT em claro

```bash
sudo tcpdump -i any port 1883
```

## Capturar MQTT com conteúdo ASCII

```bash
sudo tcpdump -i any -A port 1883
```

Aqui podes conseguir ver tópico/mensagem se estiver em claro.

## Guardar captura `.pcap`

```bash
sudo tcpdump -i any port 1883 -w mqtt_1883.pcap
```

## Capturar na bridge Proxmox

```bash
sudo tcpdump -i vmbr3 port 1883
sudo tcpdump -i vmbr4 port 1883
```

Guardar:

```bash
sudo tcpdump -i vmbr3 port 1883 -w mqtt_vmbr3.pcap
```

## Capturar MQTT com TLS

```bash
sudo tcpdump -i any port 8883
sudo tcpdump -i any -A port 8883
sudo tcpdump -i any port 8883 -w mqtt_tls_8883.pcap
```

### Interpretação

```text
1883 = MQTT sem TLS, conteúdo pode aparecer legível.
8883 = MQTT com TLS, vejo IPs/portas/sessão TCP, mas não vejo a mensagem em claro.
```

---

# Comandos “Wireshark” para todos os guiões

Isto é o que deves decorar:

```bash
sudo tcpdump -i any icmp
```

Ver ping.

```bash
sudo tcpdump -i any port 53
```

Ver DNS.

```bash
sudo tcpdump -i any port 80
```

Ver HTTP.

```bash
sudo tcpdump -i any port 1883
```

Ver MQTT sem TLS.

```bash
sudo tcpdump -i any -A port 1883
```

Ver conteúdo legível do MQTT, se estiver em claro.

```bash
sudo tcpdump -i any port 8883
```

Ver MQTT com TLS.

```bash
sudo tcpdump -i any host <IP>
```

Ver tráfego de uma máquina específica.

```bash
sudo tcpdump -i vmbr3 host <IP>
```

Ver tráfego numa bridge específica.

---

# Mini-folha para decorar antes da apresentação 🧾

```bash
# Estado da máquina
ip a
ip route
cat /etc/resolv.conf
hostname -I

# Testes base
ping -c 4 8.8.8.8
ping -c 4 google.com
dig google.com
dig @192.168.1.1 google.com

# Serviços
systemctl status apache2
systemctl status mosquitto
ss -tulpn

# Web
curl http://<IP>
wget http://<IP>

# Nmap
sudo nmap -sS -T4 <IP>
sudo nmap -sA <IP>

# MQTT
mosquitto_sub -h <IP-broker> -t teste
mosquitto_pub -h <IP-broker> -t teste -m "hello"

# MQTT remoto
mosquitto_sub -h broker.hivemq.com -p 1883 -t teste/andre
mosquitto_pub -h broker.hivemq.com -p 1883 -t teste/andre -m "ola mqtt"

# Captura tipo Wireshark
sudo tcpdump -i any icmp
sudo tcpdump -i any port 53
sudo tcpdump -i any port 80
sudo tcpdump -i any port 1883
sudo tcpdump -i any -A port 1883
sudo tcpdump -i any port 8883
sudo tcpdump -i vmbr3 port 1883 -w mqtt.pcap
```

---

# A frase mais importante

```text
O objetivo não era obrigatoriamente instalar Wireshark. O objetivo era observar tráfego. Para isso posso usar tcpdump na interface certa, guardar um ficheiro .pcap e analisar depois no Wireshark. O ponto crítico é capturar na interface/bridge por onde o tráfego realmente passa.
```
\



----

