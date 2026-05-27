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

256


