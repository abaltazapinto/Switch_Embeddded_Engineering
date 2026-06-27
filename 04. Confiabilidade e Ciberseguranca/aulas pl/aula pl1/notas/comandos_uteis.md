# Checklist de comandos úteis — Guião 1 ✅


andre
kali2026!
## 1. Ver IP e interfaces

```bash
ip -br addr
```

Mostra interfaces e IPs de forma curta.

```bash
ip -br link
```

Mostra se as interfaces estão `UP`, `DOWN` ou `UNKNOWN`.

```bash
ip route
```

Mostra rotas e gateway/default route.

---

## 2. Diagnóstico de gateway / ARP

```bash
ip neigh show dev eth0
```

Verifica se a máquina consegue descobrir o MAC do gateway.

Resultado bom:

```txt
10.42.0.1 lladdr xx:xx:xx:xx:xx:xx STALE
```

Resultado mau:

```txt
192.168.1.1 FAILED
```

Significa problema de camada 2 / ARP.

---

## 3. Testar conectividade

### Testar gateway

```bash
ping -c 3 10.42.0.1
```

Prova comunicação até ao gateway.

### Testar Internet por IP

```bash
ping -c 3 8.8.8.8
```

Prova acesso ao exterior sem depender de DNS.

### Testar DNS

```bash
ping -c 3 google.com
```

Prova que DNS funciona.

---

## 4. Testar rede isolada `vmbr3`

No CT100:

```bash
ip -br addr && ping -c 3 192.168.50.11 && ping -c 3 8.8.8.8
```

Resultado esperado:

```txt
192.168.50.11 responde ✅
8.8.8.8 falha ✅
```

Isto prova:

```txt
CT100 comunica com CT101
mas não tem Internet
```

---

## 5. Ver se SSH está ativo

No CT101:

```bash
systemctl is-active ssh
```

Ou:

```bash
systemctl is-active sshd
```

Ou ainda:

```bash
ss -tlnp | grep ':22'
```

Resultado bom:

```txt
active
```

ou uma linha com `:22`.

---

## 6. Testar SSH por password

No CT100:

```bash
ssh root@192.168.50.11
```

Se pedir password, a rede e a porta SSH estão boas.

Se aparecer isto:

```txt
root@c2:~#
```

entraste no CT101.

Para sair:

```bash
exit
```

---

## 7. Alterar password do root

No CT101:

```bash
passwd root
```

Útil quando não sabes a password do container.

---

## 8. Permitir SSH root por password

No CT101:

```bash
sed -i 's/^#\?PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config && \
sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
systemctl restart ssh
```

⚠️ Usar só em laboratório. Em produção, login SSH como root é má prática.

---

## 9. Criar chave SSH no CT100

No CT100:

```bash
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""
```

Cria:

```txt
/root/.ssh/id_ed25519      chave privada
/root/.ssh/id_ed25519.pub  chave pública
```

---

## 10. Copiar chave pública para CT101

No CT100:

```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.50.11
```

Depois testar:

```bash
ssh root@192.168.50.11
```

Se entrar sem pedir password, a autenticação por chave está feita.

---

# Comandos úteis no Proxmox host

## Ver bridges e interfaces

```bash
ip -br link
```

```bash
ip -br addr
```

```bash
bridge link
```

```bash
cat /etc/network/interfaces
```

---

## Recarregar rede no Proxmox

```bash
ifreload -a
```

Usado depois de alterar bridges como `vmbr2` ou `vmbr3`.

---

## Entrar num container pelo Proxmox

```bash
pct enter 100
```

```bash
pct enter 101
```

Útil se SSH falhar.

---

## Ver configuração de container

```bash
pct config 100
```

```bash
pct config 101
```

Procura linhas como:

```txt
net0: name=eth0,bridge=vmbr3,ip=192.168.50.10/24
```

---

## Desbloquear VM travada

```bash
qm unlock 102
```

Só usar se a VM ficou bloqueada por erro anterior.

---

## Parar VM à força

```bash
qm stop 102 --skiplock 1
```

⚠️ Só usar se shutdown normal falhar.

---

# Checklist final de validação

```bash
# Na Kali
ip -br addr
ip route
ip neigh show dev eth0
ping -c 3 10.42.0.1
ping -c 3 8.8.8.8
ping -c 3 google.com
```

```bash
# No CT100
ip -br addr
ping -c 3 192.168.50.11
ping -c 3 8.8.8.8
ssh root@192.168.50.11
```

```bash
# No CT101
systemctl is-active ssh
ss -tlnp | grep ':22'
```

```bash
# SSH key no CT100
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""
ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.50.11
ssh root@192.168.50.11
```

# Ideia central para memorizar 🧠

```txt
ip -br addr        → tenho IP?
ip route           → tenho gateway?
ip neigh show      → ARP funciona?
ping gateway       → chego à rede local?
ping 8.8.8.8       → tenho Internet por IP?
ping google.com    → DNS funciona?
ssh user@ip        → serviço aplicacional funciona?
```

**Pergunta de decisão:** queres que eu transforme isto numa folha A4 tipo “cheat sheet” para imprimir/estudar?
