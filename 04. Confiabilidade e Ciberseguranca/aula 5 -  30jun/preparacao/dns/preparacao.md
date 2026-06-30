# DNS — ideia principal

DNS significa Domain Name System.

É o sistema que traduz nomes fáceis para humanos, como:

academy.networkchuck.com

em endereços IP, como:

104.18.42.139

Analogia simples:
DNS é como a lista de contactos do telemóvel.

Eu sei o nome "Bernard", mas não sei o número.
O telemóvel procura o número por mim.

Na Internet:
Eu sei o nome do site, mas o browser precisa do IP.
O DNS procura o IP por mim.

---

# Caminho de uma pesquisa DNS

Quando escrevo um site no browser:

1. O browser pergunta ao resolver local / stub resolver.
2. Se não souber, pergunta ao DNS recursivo.
   Exemplo: DNS do ISP, Google DNS, Cloudflare, Quad9.
3. O DNS recursivo pergunta aos Root Servers.
4. Os Root Servers indicam quem trata do TLD.
   Exemplo: .com, .net, .pt.
5. O servidor TLD indica o authoritative name server.
6. O authoritative name server sabe a resposta final.
7. A resposta volta ao computador.
8. O resultado fica em cache para ser mais rápido da próxima vez.

---

# Registos DNS importantes

A record:
Nome para IPv4.

AAAA record:
Nome para IPv6.

NS record:
Indica que servidor DNS é autoridade para um domínio.

MX record:
Indica que servidores recebem e-mail para aquele domínio.

TXT record:
Guarda texto usado para segurança e verificação.

SPF:
Diz que servidores podem enviar e-mail em nome do domínio.

DKIM:
Ajuda a verificar se o e-mail foi alterado.

DMARC:
Define política para e-mails que falham SPF/DKIM.

---

# DNS e cibersegurança

DNS é crítico porque controla para onde vamos na Internet.

Se o DNS for manipulado, o utilizador pode ir para o servidor errado sem perceber.

Riscos:
- DNS spoofing
- DNS cache poisoning
- phishing
- malware domains
- redirecionamento para sites falsos
- exfiltração de dados via DNS

Defesas:
- DNSSEC: valida autenticidade das respostas DNS.
- DoH: DNS over HTTPS, cifra pedidos DNS.
- DoT: DNS over TLS, cifra pedidos DNS.
- DNS filtering: bloqueia domínios maliciosos.
- Logs DNS: ajudam a detetar máquinas infetadas.
- Redundância DNS: evita falhas de disponibilidade.

---

# Ligação à ideia do professor: analogias entre áreas

DNS pode ser visto através de várias analogias:

História / guerra:
DNS é uma cadeia de comando. Root -> TLD -> authoritative.

Biologia:
DNS filtering funciona como sistema imunitário: bloqueia agentes perigosos.

Mecânica:
Redundância DNS lembra tolerância a falhas. Se um servidor falha, outro responde.

Matemática / criptografia:
DNSSEC usa assinaturas digitais para provar que a resposta é legítima.

Informática:
Cache melhora performance, mas pode criar risco se for envenenada.

---

# Frase curta para dizer na aula

DNS não é só uma agenda telefónica da Internet. É uma infraestrutura crítica: se falhar, muitos serviços deixam de funcionar; se for manipulado, pode redirecionar utilizadores para destinos falsos. Por isso, em cibersegurança interessa perceber tanto o processo normal de resolução como as defesas: DNSSEC, DoH/DoT, filtering e monitorização de logs.