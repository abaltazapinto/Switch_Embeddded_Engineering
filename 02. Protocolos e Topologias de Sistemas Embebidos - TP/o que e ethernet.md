Manual breve sobre Ethernet
1. O que é a Ethernet
A Ethernet é uma tecnologia de rede utilizada principalmente em redes locais (LAN) — em ambientes domésticos, escritórios e data centers. Foi padronizada pelo IEEE como 802.3.
2. Meios de transmissão
A Ethernet é, por definição, uma tecnologia de rede com fios. Ao longo do tempo utilizou diferentes meios físicos:
Cabo coaxial — foi o primeiro meio físico utilizado em Ethernet: 
10BASE5 ("Thicknet"): cabo coaxial grosso, até 500 m por segmento.
10BASE2 ("Thinnet" ou "Cheapernet"): cabo coaxial fino (RG-58), até 185 m por segmento. Estas redes usavam topologia de barramento (bus), com terminadores de 50 Ω nas extremidades e CSMA/CD para gerir colisões.
Par entrançado — atualmente o mais comum em LANs (Cat5e, Cat6, Cat6a, etc.), em padrões como 10BASE-T, 100BASE-TX, 1000BASE-T.
Fibra óptica — usada em ligações de longa distância, backbones e data centers: 
100BASE-FX (100 Mbps, multimodo)
1000BASE-SX / LX (Gigabit em multimodo / monomodo)
10GBASE-SR / LR / ER (10 Gigabit, vários alcances)
40GBASE / 100GBASE / 400GBASE (alta velocidade)
Vantagens da fibra: maior largura de banda, distâncias superiores, imunidade a interferência eletromagnética e menor atenuação.
Para ligações sem fios, a tecnologia usada é o Wi-Fi (IEEE 802.11), que é distinta da Ethernet — embora frequentemente coexistam (o ponto de acesso Wi-Fi liga-se por Ethernet ao router/switch).
3. Endereço MAC
O endereço MAC (Media Access Control) na Ethernet tem 48 bits, normalmente representados em 12 dígitos hexadecimais separados por dois pontos ou hífens (ex.: 00:1A:2B:3C:4D:5E).
Estrutura, em duas partes de 24 bits:
OUI (Organizationally Unique Identifier) — primeiros 24 bits, atribuídos pelo IEEE ao fabricante.
NIC specific — últimos 24 bits, atribuídos pelo fabricante a cada interface.
Permite cerca de 281 biliões (2⁴⁸) de endereços únicos a nível mundial.
4. Ethernet no modelo OSI
A Ethernet atua nas duas camadas inferiores do modelo OSI:
Camada 1 — Física: define meios de transmissão, conectores, sinais elétricos/ópticos e codificação.
Camada 2 — Ligação de Dados: define o formato da trama (frame), o endereçamento MAC e o controlo de acesso ao meio (originalmente CSMA/CD).
A camada de ligação subdivide-se em:
LLC (Logical Link Control) — IEEE 802.2.
MAC (Media Access Control) — IEEE 802.3, a parte propriamente Ethernet.
5. Switch Ethernet
O switch é um dispositivo inteligente, distinto do hub:
Mantém uma tabela MAC (CAM table), associando endereços MAC às portas onde foram aprendidos.
Quando recebe uma trama, consulta a tabela e encaminha apenas para a porta de destino (unicast).
Envia para todas as portas (flooding) apenas em situações específicas: broadcast, multicast desconhecido, ou unicast cujo destino ainda não está na tabela.
Esta comutação seletiva reduz colisões, aumenta a largura de banda efetiva e permite que cada porta funcione no seu próprio domínio de colisão. (O hub, por oposição, envia sempre para todas as portas.)
6. Endereço IP vs Endereço MAC
Os dois endereços coexistem e atuam em camadas diferentes — não se substituem:
Endereço IP (Camada 3 — Rede): entrega fim-a-fim entre redes diferentes (routing).
Endereço MAC (Camada 2 — Ligação de Dados): entrega salto a salto dentro do mesmo segmento Ethernet.
Numa LAN, um dispositivo conhece tipicamente o IP de destino, mas precisa do MAC correspondente para construir a trama Ethernet. Para isso usa o protocolo ARP (Address Resolution Protocol), que faz o mapeamento IP → MAC.
A trama transporta ambos: cabeçalho Ethernet com MACs de origem/destino, e dentro dela o pacote IP com os endereços IP de origem/destino.

Brief Ethernet Manual
1. What is Ethernet
Ethernet is a networking technology used primarily in local area networks (LANs) — in homes, offices, and data centers. It was standardized by the IEEE as 802.3.
2. Transmission Media
Ethernet is, by definition, a wired networking technology. Over time it has used different physical media:
Coaxial cable — the first physical medium used in Ethernet: 
10BASE5 ("Thicknet"): thick coaxial cable, up to 500 m per segment.
10BASE2 ("Thinnet" or "Cheapernet"): thin coaxial cable (RG-58), up to 185 m per segment.
These networks used a bus topology, with 50 Ω terminators at each end and CSMA/CD to handle collisions.
Twisted pair — currently the most common in LANs (Cat5e, Cat6, Cat6a, etc.), in standards such as 10BASE-T, 100BASE-TX, and 1000BASE-T.
Fiber optic — used in long-distance links, backbones, and data centers: 
100BASE-FX (100 Mbps, multimode)
1000BASE-SX / LX (Gigabit on multimode / single-mode)
10GBASE-SR / LR / ER (10 Gigabit, various reaches)
40GBASE / 100GBASE / 400GBASE (high-speed)
Advantages of fiber: greater bandwidth, longer distances, immunity to electromagnetic interference, and lower attenuation.
For wireless connections, the technology used is Wi-Fi (IEEE 802.11), which is distinct from Ethernet — although they often coexist (the Wi-Fi access point connects to the router/switch via Ethernet).
3. MAC Address
The MAC (Media Access Control) address in Ethernet is 48 bits long, typically represented as 12 hexadecimal digits separated by colons or hyphens (e.g., 00:1A:2B:3C:4D:5E).
Structure, in two 24-bit parts:
OUI (Organizationally Unique Identifier) — the first 24 bits, assigned by the IEEE to the manufacturer.
NIC specific — the last 24 bits, assigned by the manufacturer to each interface.
This allows for about 281 trillion (2⁴⁸) unique addresses worldwide.
4. Ethernet in the OSI Model
Ethernet operates at the two lowest layers of the OSI model:
Layer 1 — Physical: defines transmission media, connectors, electrical/optical signals, and encoding.
Layer 2 — Data Link: defines the frame format, MAC addressing, and medium access control (originally CSMA/CD).
The Data Link layer is subdivided into:
LLC (Logical Link Control) — IEEE 802.2.
MAC (Media Access Control) — IEEE 802.3, which is the Ethernet part proper.
5. Ethernet Switch
A switch is an intelligent device, distinct from a hub:
It maintains a MAC table (CAM table), mapping MAC addresses to the ports on which they were learned.
When it receives a frame, it consults the table and forwards it only to the destination port (unicast).
It sends to all ports (flooding) only in specific situations: broadcasts, unknown multicast, or unicast whose destination is not yet in the table.
This selective switching reduces collisions, increases effective bandwidth, and lets each port operate in its own collision domain. (A hub, by contrast, always sends to all ports.)
6. IP Address vs. MAC Address
The two addresses coexist and operate at different layers — they do not replace each other:
IP address (Layer 3 — Network): end-to-end delivery between different networks (routing).
MAC address (Layer 2 — Data Link): hop-by-hop delivery within the same Ethernet segment.
On a LAN, a device typically knows the destination IP, but needs the corresponding MAC to build the Ethernet frame. For this it uses the ARP (Address Resolution Protocol), which performs the IP → MAC mapping.
The frame carries both: an Ethernet header with source/destination MACs, and inside it the IP packet with source/destination IP addresses.

