Sim. **A partir de agora não fechamos nenhum Lab sem passar pelas Questões de Reflexão Crítica.** No Lab 1 saltámos essa parte; corrigimos já.

O guião coloca três questões sobre SDN, isolamento e persistência/IPAM. lab1 As respostas abaixo são a explicação para estudo/oral — o PDF apresenta as perguntas, não as respostas.

### Lab 1 — Questão 1: SDN vs. Linux Bridges

Uma bridge Linux tradicional é configurada diretamente no host, por exemplo em `/etc/network/interfaces`. É uma abordagem mais **manual e imperativa**: criamos `vmbr0`, definimos portas, IPs, rotas, etc., máquina a máquina.

Com **Proxmox SDN**, trabalhamos num nível mais alto:

```text
Zone
 └── VNet
      └── Subnet
           ├── Gateway
           ├── DHCP
           ├── IPAM
           └── SNAT
```

No nosso Lab 1 fizemos precisamente isso: `ZoneEdge`, duas VNETs, duas subnets, DHCP e SNAT. A VM recebeu automaticamente `10.10.10.100` e o LXC `172.16.0.100`.

O **IPAM** centraliza a gestão dos endereços e o DHCP atribui-os automaticamente. Isto reduz erros e torna muito mais simples criar dezenas ou centenas de máquinas Edge/Fog.

O próprio guião contrasta PVE 8, onde havia mais instalação/configuração manual de plugins e `dnsmasq`, com PVE 9, onde a SDN está mais integrada e o firewall evolui para `nftables`. lab1

**Resposta curta para oral:**  
> Linux bridges são configuração de baixo nível por host. SDN abstrai a rede em Zones, VNETs e Subnets e integra IPAM/DHCP, permitindo automatização e gestão centralizada em escala.

---

### Lab 1 — Questão 2: porque é que o DHCP de uma VNET não interfere com a outra?

Porque **DMZ e Intranet são domínios L2 separados**.

No nosso caso:

```text
DMZ
10.10.10.0/24
VM → 10.10.10.100

        ≠ broadcast domain

Intranet
172.16.0.0/24
LXC → 172.16.0.100
```

Um pedido DHCP é inicialmente **broadcast L2**. O broadcast da DMZ não é simplesmente despejado para a Intranet; cada VNET tem a sua separação lógica e configuração de DHCP/subnet.

A comunicação entre redes, quando permitida, passa depois por **L3/gateway/routing**, onde podem ser aplicadas regras de firewall.

É precisamente isso que a questão do guião pretende relacionar com `ebtables/iptables` no modelo antigo e `nftables` no PVE 9. lab1

**Resposta curta para oral:**  
> Cada VNET constitui um domínio L2 separado, portanto os broadcasts DHCP ficam isolados. A comunicação entre VNETs ocorre em L3 e pode ser controlada pelo firewall.

---

### Lab 1 — Questão 3: leases DHCP, reboot e migração

Aqui há três conceitos que convém **não misturar**:

```text
IPAM
→ conhece a estrutura/endereço das redes

DHCP
→ entrega dinamicamente um IP ao cliente

Lease
→ registo temporário IP ↔ cliente/MAC
```

O `dnsmasq` mantém os leases em ficheiros como os indicados no guião em `/var/lib/pve-sdn/dnsmasq/`. lab1

Quando uma VM reinicia, normalmente continua com a mesma **MAC address**. O DHCP consegue reconhecer esse cliente e, enquanto a informação de lease for válida/disponível, tende a manter o mesmo endereço.

Num cluster, a parte importante é que a **configuração SDN/IPAM é gerida pela infraestrutura Proxmox**, enquanto o serviço DHCP efetivo é executado onde a rede está ativa. Numa migração, a rede tem de continuar a conhecer a VNET/subnet e a disponibilizar DHCP no nó de destino.

O PVE 9 torna esta gestão muito mais integrada; não é necessário imaginar que “o ficheiro `.leases` sozinho resolve o cluster”. É a combinação de **configuração SDN + IPAM + DHCP + identidade da VM/MAC** que mantém consistência.

**Resposta curta para oral:**  
> O lease associa temporariamente uma MAC a um IP. A configuração de rede e IPAM mantém a visão da subnet, enquanto o DHCP mantém as atribuições. Em reboot ou migração, a identidade MAC e a configuração SDN permitem restabelecer consistentemente o endereçamento.

---

E há uma ligação importante entre o **Lab 1 e o Lab 2** que acabaste de experimentar:

```text
LAB 1
Desired network state
→ Proxmox SDN cria/maintém a infraestrutura

LAB 2
Desired application state
→ Kubernetes cria/maintém os Pods
```

É a mesma ideia de **abstração + automatização**, aplicada em camadas diferentes.

No Lab 2 acabaste de ver isso de forma brutalmente clara: disseste ao Kubernetes **“quero 5 réplicas”**, apagaste uma, e o sistema corrigiu o estado real para voltar ao estado desejado.

Quando terminarmos o Portainer, **antes de dizer que o Lab 2 está concluído fazemos obrigatoriamente as três questões de reflexão crítica do Lab 2**. lab2 
