## Resumo ultra-curto — Guiões 1 a 5

| Guião                                          | Resumo para exame                                                                                                                                                  |
| ---------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Guião 1 — Virtualização / Proxmox / Linux**  | Criaste máquinas/containers no Proxmox e validaste rede básica com IP, gateway, ping, SSH/Apache. Prova: saber pôr máquinas a comunicar e confirmar conectividade. |
| **Guião 2 — OPNsense / Firewall / nmap**       | Instalaste/configuraste OPNsense e testaste portas/regras com `nmap`. Prova: perceber diferença entre porta `open`, `closed` e `filtered`.                         |
| **Guião 3 — NAT / DHCP / LAN-WAN**             | Configuraste cliente atrás da OPNsense com DHCP/NAT para sair para a Internet. Prova: cliente privado consegue Internet através da firewall/gateway.               |
| **Guião 4 — Regras de firewall / segmentação** | Criaste políticas para permitir/bloquear tráfego entre redes/máquinas. Prova: segurança por controlo explícito do que entra/sai entre segmentos.                   |
| **Guião 5 — MQTT / broker / TLS**              | Testaste MQTT local/remoto na porta `1883` e MQTT com TLS na `8883`. Prova: distinguir comunicação IoT sem encriptação vs comunicação protegida com certificados.  |

## Frase geral para oral

> A cadeira mostra como montar uma infraestrutura virtual, segmentar redes com firewall, validar tráfego com ferramentas como `ping`, `nmap` e `tcpdump`, e comparar comunicações inseguras e seguras, como MQTT em `1883` versus MQTT/TLS em `8883`.

Vai comer agora. Depois estudas pelos conceitos, não pelos comandos.
