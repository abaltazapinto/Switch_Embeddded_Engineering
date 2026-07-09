# Pitch 2 minutos — VLANs contra movimentos laterais

## Mensagem central

**VLANs não impedem a intrusão inicial. Elas impedem que uma máquina comprometida se transforme numa porta aberta para toda a rede.**

---

## Estrutura com tempo

### 0:00–0:20 — Gancho

Numa rede plana, quando um atacante compromete um computador, o problema raramente fica nesse computador. O atacante tenta mover-se lateralmente: descobrir máquinas, procurar serviços vulneráveis e chegar a sistemas mais críticos.

### 0:20–0:45 — Movimento lateral

Movimento lateral é a progressão dentro da rede depois da primeira entrada. Por exemplo: primeiro entra num PC de utilizador, depois tenta chegar a servidores, impressoras, NAS, bases de dados ou equipamentos de administração.

### 0:45–1:20 — VLANs com analogia

A segmentação por VLANs é como dividir um navio em compartimentos estanques. Se um compartimento for comprometido, o dano fica limitado. Em vez de todos os dispositivos estarem na mesma rede, criamos zonas: utilizadores, servidores, IoT, gestão, convidados.

### 1:20–1:45 — Técnica essencial

Cada VLAN cria um domínio lógico separado. O tráfego entre VLANs deve passar por um router ou firewall, onde aplicamos regras: quem pode falar com quem, em que portas e com que serviços. O objetivo não é só separar, é controlar.

### 1:45–2:00 — Conclusão forte

Por isso, VLANs são um antídoto contra movimentos laterais porque reduzem a superfície de ataque interna. Não impedem a intrusão inicial, mas impedem que uma máquina comprometida se transforme numa porta aberta para toda a rede.

---

## Palavras-chave para dizer

- rede plana
- movimento lateral
- segmentação
- VLAN
- domínio lógico separado
- router/firewall
- regras entre VLANs
- superfície de ataque interna

---

## Versão de emergência — se estiveres sem tempo

Numa rede plana, um atacante que compromete um PC pode tentar mover-se lateralmente para servidores, NAS, impressoras ou sistemas críticos. As VLANs reduzem esse risco porque dividem a rede em zonas lógicas, como compartimentos estanques num navio. O tráfego entre zonas passa por uma firewall, onde se definem regras. Portanto, VLANs não impedem a entrada inicial, mas limitam a propagação do ataque.

---

## Perguntas rápidas que podem aparecer

**O que é movimento lateral?**  
É a progressão do atacante dentro da rede depois da primeira máquina comprometida.

**O que faz uma VLAN?**  
Separa logicamente dispositivos dentro da mesma infraestrutura física.

**Porque não basta criar VLANs?**  
Porque é preciso controlar o tráfego entre elas com router/firewall e regras.

**Qual é o objetivo de segurança?**  
Reduzir a superfície de ataque interna e limitar a propagação.
