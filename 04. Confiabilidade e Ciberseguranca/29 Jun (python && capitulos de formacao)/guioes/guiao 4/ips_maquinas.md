# Guião 4 — IPs das máquinas

## Firewall — OPNsense `103 (opnsense-fw)`

| Interface | Nome OPNsense | Bridge Proxmox | IP |
|---|---|---|---|
| WAN | `vtnet0` | `vmbr2` | `10.42.0.227/24` |
| LAN | `vtnet1` | `vmbr3` | `192.168.1.1/24` |
| LAN2 / OPT1 | `vtnet2` | `vmbr4` | `192.168.2.1/24` |

---

## Proxmox host `pve`

| Interface | IP | Função |
|---|---|---|
| `vmbr0` | `10.0.2.15/24` | acesso Proxmox |
| `vmbr4` | `192.168.2.254/24` | acesso direto/teste à LAN2 |

---

## Containers

| CT ID | Nome | Bridge | IP | Gateway | Estado |
|---|---|---|---|---|---|
| `106` | `ubuntu1-lan` | `vmbr3` | `192.168.1.182/24` | `192.168.1.1` | LAN original |
| `105` | `ubuntu-lan2` | `vmbr4` | `192.168.2.100/24` | `192.168.2.1` | LAN2 / OPT1 |

---

## Testes já validados

```bash
# ubuntu1-lan -> Internet
ping -c 4 8.8.8.8
# OK

# ubuntu1-lan -> ubuntu-lan2
ping -c 4 192.168.2.100
# OK

# ubuntu1-lan -> servidor web no ubuntu-lan2
wget -O- http://192.168.2.100/
# OK: HTTP 200

## Testes inter-LAN — Guião 4

### 3.2.1 — ubuntu1-lan -> ubuntu2-lan2

```bash
ping -c 4 192.168.2.100
wget -O- http://192.168.2.100/


## Objetivo

Fechar a evidência antes de começares o **3.2.3**, porque no próximo passo vais restringir regras e alguns pings podem deixar de funcionar.

## Como pensar

Neste momento as regras estão permissivas demais.  
O **3.2.3** vai pedir algo mais fino:

```text
permitir página web
bloquear o resto entre máquinas
manter Internet

---

