# Conceito

- Modelo OSI

# O que tens de saber

- 7 camadas: Fisica, Ligacao, Rede, Transporte, Sessao, Apresentacao, Aplicacao. 

# Erro tipico 

- Confundir IP com camada 2 ou TCP com camda 3. 

# Mini pergunta

- Em que camada esta o IP?

Penso que esta na Camada 3 (Rede) do modelo OSI. 

Nesta camada, o IP e responsavel por:

	. Enderecamento logico: Utiliza enderecos IP (IPv4 ou IPv6) para identificar origem e destino.

	. Roteamento: Seleciona os melhores caminhos para encaminhar pacotes entre diferentes redes. 

	. Fragmentacao: Divide pacotes grandes para se adequarem ao tamanho maximo de transmissao (MTU) dos enlaces fisicos. 

No modelo TCP IP, que possui apenas 4 camadas, o IP corresponde a Camada de Internet. 
---

# Conceito

- TCP/IP 

# O que tens de saber

- Aplicacao, Transporte, Rede, Fisico + DLL

# Erro tipico

- Decorar sem saber encapsulento.

# Mini-pergunta

- TCP pertence a que camada ? 

	O tcp pertemce tambem a camada rede no modelo osi acho

--- 

# Conceito

- Encapsulamento 

# O que tens de saber

- Dados recebem cabecalhos ao descer a pilha. 

# Erro tipico

- Pensar que Ethernet "leva TCP diretamente"

# Mini pergunta

- Que cabecalho identifica se vem IP ou ARP?

# Erro tipico

- Pensar que Ethernet "leva TCP diretamente"

# Mini pergunta

- Que cabecalho identifica se vem IP ou ARP?

	O cabecalho que identifica se o payload do quadro Ethernet e um pacote IP ou ARP e o campo EtherType, localizado no proprio cabecalho do quadro Ethernet.

	. EtherType = 0x0800: Indica que o payload e um pacote IP (IPV4)
	. EtherType = 0x0806: Indica que o payload e um pacote ARP. 

	Este e um campo e essencial para que o dispositivo receptor saiba como interpretar e processar os dados que seguem no quadro. 

---

# Conceito

- IPV4

# O que tens de saber

- Endereco de 32 bits; rede = IP AND mascara

# Erro tipico

- Somar valores em vez de usar blocos.

# Mini - pergunta

- Quantos enderecos tem uma rede /24 ? 

	255


---

# Conceito 

- Mascara  / CIDR 

# O que tens de saber

- /n indica bits de rede; hosts = 32 - n

# Erro tipico

- Confundir enderecos totais com hosts validos

- Usar broadcast como host valido

# Mini-pergunta

- Quantos host validos ha num /26 ? 

	penso que 32 - 26 = 6 | logo ha (2^6)  - 1 = 63.

---

# Conceito

- Broadcast IPv4

# O que tens de saber 

- Ultimo endereco da sub-rede

# Erro tipico

- Usar broadcast como host valido

# Mini - pergunta

- Numa rede /30, quantos hosts validos existem ?

	Penso que 32-30 = 2^2 -1 = 3

---

# Conceito

- ARP

# O que tens de saber

- Resolve IPv4 -> MAC dentro da LAN

# Erro tipico

- Pensar que ARP atravessa routers

# Mini pergunta

- ARP funciona entre redes diferentes ? 

---

# Conceito 

- ICMP

# O que tens de saber

- Diagnostico / controlo; usado por ping

# Erro tipico

- Confundir ICMP com TCP/UDP

# Mini pergunta

- O ping usa TCP, UDP ou ICMP ? 

	Penso que usa ICMP 
