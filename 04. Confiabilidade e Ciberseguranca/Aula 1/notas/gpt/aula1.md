# Aula 1 — Reconstrução da aula a partir do SRT 🧭

**Fonte principal:** `2026-06-15 19-11-12.srt`
**Slides usados para clarificar:** `2 - criptografia-en.pdf`
**Nota importante:** o SRT cobre **só parte** do PDF. Os temas finais dos slides — hashes, TLS, WireGuard, pós-quântica, IoT encryption — aparecem no PDF, mas **não foram claramente dados nesta gravação**.

---

## 1. Reconstruct the Lecture

### 1.1. Introdução: ambiente de trabalho e virtualização

O professor começou por explicar que a cadeira vai usar ferramentas práticas, gratuitas e utilizáveis no dia a dia.

Falou de várias soluções de virtualização:

| Transcrição SRT | Interpretação provável |
| --------------- | ---------------------- |
| “Hyper-D”       | Hyper-V                |
| “Vmoer”         | VMware                 |
| “BoxMox”        | Proxmox                |
| “OpenSense”     | OPNsense               |
| “SPS-32”        | ESP32                  |

A ideia central não era ensinar virtualização em profundidade, mas usar virtualização como **laboratório controlado**.

### Ideia principal

A cadeira vai usar máquinas virtuais e containers para simular ambientes de cibersegurança e sistemas embebidos.

O professor justificou isto assim:

* usar hardware real consome muito tempo;
* os alunos têm níveis diferentes;
* configurar ESP32, MicroPython ou Node-RED pode atrasar o objetivo principal;
* a prioridade é perceber conceitos de segurança, comunicação e proteção.

### Visão de sistemas embebidos

O professor fez questão de alargar a definição de “sistema embebido”.

Não é só:

* ESP32;
* sensores;
* microcontroladores.

Também pode ser:

* televisão Android;
* câmara IP;
* contador inteligente;
* dispositivos IoT comerciais.

A preocupação dele é especialmente com dispositivos que **não sabemos exatamente o que fazem por dentro**.

Exemplo mental:

> Um ESP32 teu é controlável.
> Uma câmara IP barata, uma televisão Android ou um contador inteligente podem comunicar com serviços externos sem tu saberes exatamente como.

---

### 1.2. Ferramentas práticas previstas

O professor referiu que vão trabalhar com:

* **Proxmox** — máquinas virtuais e containers;
* **OPNsense** — firewall, regras, proteção de rede;
* **MQTT** — protocolo muito usado em sistemas embebidos/IoT;
* **clientes Python** — para simular recolha/envio de dados;
* IPv4 principalmente, porque IPv6/CoAP seria mais complexo para esta fase.

Ponto importante:

> O laboratório é uma simulação realista para estudar segurança em sistemas embebidos, sem depender logo de hardware físico.

---

## 1.3. Entrada no tema: fundamentos de criptografia

Depois da introdução prática, a aula passou para **criptografia**.

O professor perguntou se os alunos tinham noção de criptografia e começou com uma explicação histórica.

### Criptografia

Criptografia é usada para permitir comunicação segura mesmo quando alguém pode interceptar a comunicação.

O professor introduziu a ideia de:

* comunicação interceptável;
* ataque “homem no meio”;
* necessidade de proteger mensagens.

### Ataque homem-no-meio

O professor explicou que devemos assumir que uma comunicação pode ser interceptada.

Exemplo simples:

> Se um dispositivo IoT comunica por Wi-Fi, rádio ou rede local, alguém pode tentar escutar ou alterar essa comunicação.

Por isso, em teoria, deveríamos usar criptografia.

Mas o professor avisou uma coisa importante:

> Só porque a criptografia existe, não significa que todos os dispositivos embebidos a usem bem.

Exemplos mencionados/implícitos:

* televisão Android a controlar uma luz;
* contador inteligente;
* dispositivos IoT que comunicam sem proteção adequada.

---

## 1.4. Conceitos base: encriptação, desencriptação, cifra e chave

A comunicação protegida envolve duas fases:

| Conceito       | Explicação simples                                |
| -------------- | ------------------------------------------------- |
| Encriptação    | transformar mensagem legível em mensagem ilegível |
| Desencriptação | transformar mensagem ilegível em mensagem legível |
| Cifra          | algoritmo matemático usado no processo            |
| Chave          | valor secreto usado pelo algoritmo                |

Modelo mental:

```text
Mensagem original + algoritmo + chave
        ↓
Mensagem cifrada
        ↓
Algoritmo + chave correta
        ↓
Mensagem original
```

A chave é essencial. Saber só o algoritmo não deve ser suficiente para recuperar a mensagem.

---

## 1.5. História da criptografia

O professor deu exemplos históricos para mostrar que criptografia não é algo novo.

### Cifra de César

Um dos primeiros exemplos clássicos.

Ideia:

* avançar letras no alfabeto;
* a chave é o número de posições.

Exemplo:

```text
A → D
B → E
C → F
```

Se a chave for 3, cada letra anda três posições.

### Segunda Guerra Mundial

O professor referiu que a criptografia teve grande importância na guerra.

Temas mencionados:

* Enigma;
* Alan Turing;
* máquinas usadas para quebrar mensagens;
* ligação entre criptografia e nascimento da computação moderna.

A ideia importante para a cadeira:

> A criptografia não é só matemática abstrata. Ela teve impacto direto em guerra, computação e segurança moderna.

---

## 1.6. Criptografia simétrica

Aqui começou a parte técnica mais importante.

### Definição

Na criptografia simétrica, o emissor e o recetor usam **a mesma chave**.

```text
Emissor usa chave K para encriptar
Recetor usa a mesma chave K para desencriptar
```

Modelo mental:

> É como uma única chave física que abre e fecha a mesma caixa.

### Vantagens

* simples;
* rápida;
* eficiente;
* boa para grandes volumes de dados.

### Problema principal

A mesma chave tem de ser conhecida pelos dois lados.

Pergunta crítica:

> Como entregar a chave ao outro lado sem alguém a roubar?

Esse problema leva à necessidade de criptografia assimétrica ou de handshakes seguros.

### AES

O algoritmo simétrico mais referido foi o **AES**.

Pelos slides:

* AES é usado como standard desde 2002;
* variantes: AES-128, AES-192, AES-256;
* usa transformações internas sobre blocos/matrizes de dados;
* é usado em software, discos cifrados e comunicações.

Exemplos referidos:

* WhatsApp;
* BitLocker.

---

## 1.7. Exemplo: BitLocker e ataques físicos

O professor mencionou que há vídeos/demonstrações onde é possível atacar sistemas de encriptação de disco se a chave passar de forma observável no hardware.

A ideia não é que “BitLocker é inútil”.

A ideia é:

> Criptografia forte pode falhar se a implementação, o hardware ou o processo de arranque expuserem a chave.

Para sistemas embebidos, isto é importante porque muitas vezes o atacante pode ter acesso físico ao dispositivo.

---

## 1.8. Criptografia assimétrica

Depois veio a criptografia assimétrica.

### Definição

Na criptografia assimétrica existem duas chaves:

| Chave   | Função              |
| ------- | ------------------- |
| Pública | pode ser partilhada |
| Privada | deve ficar secreta  |

Modelo mental:

> A chave pública é como uma caixa de correio onde todos podem pôr mensagens.
> A chave privada é a única chave que permite abrir essa caixa.

### Uso 1: confidencialidade

Alguém usa a tua chave pública para encriptar uma mensagem.

Só tu, com a chave privada, consegues desencriptar.

```text
Mensagem + chave pública do recetor → mensagem cifrada
Mensagem cifrada + chave privada do recetor → mensagem original
```

### Uso 2: assinatura digital

O professor deu o exemplo do **Cartão de Cidadão**.

Quem assina usa a chave privada.

Quem verifica usa a chave pública.

```text
Assinar: chave privada
Verificar: chave pública
```

Ideia essencial:

> A assinatura digital prova que quem assinou tinha acesso à chave privada.

---

## 1.9. RSA

O professor referiu o RSA como algoritmo clássico e muito usado.

Ideia principal:

* baseado em problemas matemáticos difíceis;
* usa números primos;
* exige chaves grandes;
* usado em assinaturas digitais e encriptação.

Ponto de principiante:

> Multiplicar dois números primos grandes é fácil.
> Descobrir quais foram os dois primos originais a partir do resultado é muito difícil.

Essa assimetria é a base de segurança do RSA.

---

## 1.10. ECC — Elliptic Curve Cryptography

O professor depois comparou RSA com ECC.

### Ideia principal

ECC permite segurança equivalente com chaves menores.

Isto interessa para:

* dispositivos móveis;
* IoT;
* sistemas embebidos;
* dispositivos com menos CPU, memória e energia.

### Comparação simples

| Critério            | RSA         | ECC                 |
| ------------------- | ----------- | ------------------- |
| Chave               | maior       | menor               |
| Custo computacional | maior       | menor               |
| Uso histórico       | muito usado | cada vez mais usado |
| Interesse em IoT    | menor       | maior               |

O professor também mencionou a polémica de algoritmos propostos por entidades como NSA/NIST e a desconfiança criada por suspeitas/backdoors.

A ideia importante não é decorar a polémica.

A ideia importante é:

> Em segurança, não basta o algoritmo ser matematicamente bonito. Também interessa confiança, implementação, standards e historial.

---

# 2. Explain difficult parts simply

## Criptografia simétrica vs assimétrica

### Simétrica

Uma chave só.

```text
A mesma chave fecha e abre.
```

Boa para velocidade.

Problema: distribuir a chave com segurança.

### Assimétrica

Duas chaves.

```text
Uma chave pública.
Uma chave privada.
```

Boa para identificação, troca inicial de segredo e assinatura.

Problema: mais pesada computacionalmente.

---

## Ataque homem-no-meio

Imagina duas pessoas a conversar por cartas.

Um atacante mete-se no meio:

```text
Pessoa A → Atacante → Pessoa B
```

O atacante pode:

* ler;
* alterar;
* reenviar;
* fingir ser uma das partes.

Criptografia ajuda a impedir que ele perceba ou altere a mensagem sem ser detetado.

---

## Assinatura digital

Assinatura digital não é o mesmo que esconder a mensagem.

Ela serve para provar:

* quem assinou;
* que o conteúdo não foi alterado.

Modelo mental:

> Encriptação protege segredo.
> Assinatura protege autenticidade e integridade.

---

## Porque ECC é interessante para embebidos

Sistemas embebidos podem ter:

* pouca memória;
* pouca bateria;
* CPU fraco;
* necessidade de comunicação rápida.

ECC pode dar segurança forte com chaves menores, logo tende a consumir menos recursos.

---

# 3. Detect and correct issues / unclear parts

## 3.1. Erros claros da transcrição SRT

A transcrição automática tem muitos erros. Correções prováveis:

| SRT                       | Correto provável  |
| ------------------------- | ----------------- |
| Hyper-D                   | Hyper-V           |
| Vmoer                     | VMware            |
| BoxMox                    | Proxmox           |
| OpenSense                 | OPNsense          |
| SPS-32                    | ESP32             |
| Cretão Ciudadão           | Cartão de Cidadão |
| NECA                      | NSA               |
| incriptação / equilitação | encriptação       |
| desincriptação            | desencriptação    |
| homem do meio             | man-in-the-middle |

---

## 3.2. Parte confusa sobre AES e números primos

No SRT há uma zona em que aparecem “números primos” perto da explicação de AES.

Isto está confuso.

Correção para estudar:

* **AES** → criptografia simétrica, transformações em blocos/matrizes.
* **RSA** → criptografia assimétrica, números primos/fatorização.

Para exame, não misturar:

```text
AES ≠ números primos
RSA = números primos
```

---

## 3.3. Slides que não foram claramente cobertos

Estes tópicos aparecem no PDF, mas **Not clearly covered in the lecture**:

* algoritmos pós-quânticos: ML-KEM, ML-DSA, SLH-DSA;
* TLS/SSL handshake;
* WireGuard;
* funções hash;
* SHA-256, MD5, SHA-1;
* aplicação detalhada em MQTT, BLE, Thread/Matter;
* Mirai botnet.

Podem ser importantes na cadeira, mas **não devem ser tratados como matéria explicada nesta aula 1 pelo SRT**.

---

## 3.4. ECC no slide está demasiado simplificado

O slide apresenta ECC de forma muito comprimida e matemática.

Para esta fase, não precisas de dominar a equação.

O essencial é:

```text
ECC = criptografia assimétrica eficiente para chaves menores.
```

---

# 4. 30-Min Notebook Summary

## Aula 1 — resumo para escrever à mão

### Objetivo da aula

* Apresentar ferramentas da cadeira.
* Explicar por que se usa virtualização.
* Introduzir criptografia.
* Comparar criptografia simétrica e assimétrica.
* Mostrar relevância para sistemas embebidos/IoT.

---

### Laboratório / ferramentas

* A cadeira usa ferramentas gratuitas.
* Virtualização permite simular redes e sistemas.
* Proxmox permite:

  * máquinas virtuais;
  * containers.
* OPNsense será usado para:

  * firewall;
  * regras;
  * proteção de rede.
* MQTT será usado porque é comum em IoT/sistemas embebidos.
* IPv4 será usado por simplicidade.

---

### Sistemas embebidos — visão da cadeira

* Não são só microcontroladores.
* Também incluem:

  * câmaras IP;
  * TVs Android;
  * contadores inteligentes;
  * dispositivos IoT comerciais.
* Problema principal:

  * muitas vezes não sabemos o que comunicam;
  * podem não usar criptografia;
  * podem ter autenticação fraca.

---

### Criptografia

* Área que protege comunicação.
* Assume que alguém pode interceptar mensagens.
* Protege contra leitura/alteração indevida.

Conceitos:

* Encriptação: mensagem legível → ilegível.
* Desencriptação: mensagem ilegível → legível.
* Cifra: algoritmo matemático.
* Chave: segredo usado pelo algoritmo.

---

### Ataque homem-no-meio

* Atacante fica entre emissor e recetor.
* Pode ler, alterar ou reenviar mensagens.
* Criptografia reduz o risco.

---

### História

* Cifra de César:

  * deslocamento de letras;
  * chave = número de posições.
* Segunda Guerra Mundial:

  * Enigma;
  * Turing;
  * criptografia ligada ao nascimento da computação moderna.

---

### Criptografia simétrica

* Uma só chave.
* Mesma chave encripta e desencripta.
* Vantagens:

  * rápida;
  * simples;
  * eficiente.
* Problema:

  * como partilhar a chave em segurança?

Exemplo:

* AES.
* BitLocker.
* WhatsApp.

---

### AES

* Algoritmo simétrico.
* Standard moderno.
* AES-128, AES-192, AES-256.
* Trabalha com blocos/matrizes.
* Não confundir com RSA.

---

### Criptografia assimétrica

* Usa duas chaves:

  * pública;
  * privada.
* Chave pública pode ser partilhada.
* Chave privada deve ficar secreta.

Usos:

* Encriptação com chave pública.
* Desencriptação com chave privada.
* Assinatura digital com chave privada.
* Verificação com chave pública.

---

### Assinatura digital

* Não serve principalmente para esconder.
* Serve para provar:

  * autenticidade;
  * integridade;
  * origem.

Exemplo:

* Cartão de Cidadão.
* Assinar usa chave privada.
* Verificar usa chave pública.

---

### RSA

* Algoritmo assimétrico.
* Usa matemática com números primos.
* Chaves grandes.
* Muito usado historicamente.
* Pode ser pesado para sistemas embebidos.

---

### ECC

* Criptografia assimétrica com curvas elípticas.
* Chaves menores.
* Mais eficiente.
* Útil para:

  * IoT;
  * dispositivos móveis;
  * sistemas embebidos.

---

### Ideia final

* Segurança não é só escolher algoritmo.
* Também depende de:

  * implementação;
  * gestão de chaves;
  * hardware;
  * confiança nos standards;
  * uso correto.

---

# 5. Core Concepts — hard ones only

## 1. Chave pública vs chave privada

A chave pública pode ser dada a qualquer pessoa.

A chave privada nunca deve sair do dono.

Pensamento certo:

```text
Pública = para os outros usarem.
Privada = para eu proteger.
```

---

## 2. Encriptação vs assinatura digital

Não são a mesma coisa.

| Ação        | Serve para                 |
| ----------- | -------------------------- |
| Encriptação | esconder conteúdo          |
| Assinatura  | provar autoria/integridade |

Erro comum:

> Pensar que assinatura digital é “encriptar o documento”.
> Não é bem isso. É provar que o documento foi assinado por quem tem a chave privada.

---

## 3. Simétrica vs assimétrica

Simétrica é rápida, mas exige partilhar segredo.

Assimétrica resolve melhor identidade e troca inicial, mas é mais pesada.

Modelo usado na prática:

```text
Assimétrica para iniciar confiança.
Simétrica para transmitir dados rapidamente.
```

---

## 4. Porque isto interessa em IoT

Dispositivos IoT podem comunicar sem proteção forte.

Mesmo que exista criptografia, pode haver falhas em:

* passwords de fábrica;
* firmware fraco;
* chaves mal guardadas;
* comunicações sem TLS;
* hardware exposto.

---

# 6. Essential Exam Questions

## Conceptual 1

**Pergunta:** Qual é a diferença principal entre criptografia simétrica e assimétrica?

**Resposta:**
Na simétrica usa-se a mesma chave para encriptar e desencriptar. Na assimétrica usam-se duas chaves: uma pública e uma privada.

**Raciocínio:**
Simétrica é mais simples e rápida; assimétrica resolve melhor problemas de identidade e partilha inicial de segredo.

---

## Conceptual 2

**Pergunta:** Para que serve uma assinatura digital?

**Resposta:**
Serve para provar autenticidade e integridade de uma mensagem ou documento.

**Raciocínio:**
Quem assina usa a chave privada; quem verifica usa a chave pública.

---

## Practical 1

**Pergunta:** Num laboratório com OPNsense, Proxmox e MQTT, por que usar máquinas virtuais em vez de hardware real?

**Resposta:**
Porque as VMs permitem simular redes e dispositivos de forma mais controlada, rápida e repetível.

**Raciocínio:**
Hardware real pode exigir muito tempo de configuração e causar problemas diferentes entre alunos.

---

## Practical 2

**Pergunta:** Um dispositivo IoT envia dados por Wi-Fi sem encriptação. Qual é o risco principal?

**Resposta:**
Um atacante pode interceptar a comunicação e ler ou alterar dados.

**Raciocínio:**
Isto corresponde ao risco de ataque homem-no-meio ou escuta passiva.

---

## Multiple choice

**Pergunta:** Qual algoritmo foi apresentado como exemplo principal de criptografia simétrica?

A. RSA
B. AES
C. ECC
D. Cartão de Cidadão

**Resposta:** B. AES

**Raciocínio:**
AES é simétrico. RSA e ECC são assimétricos. Cartão de Cidadão foi usado como exemplo de assinatura digital.

---

# 7. Common Pitfalls

## 1. Confundir AES com RSA

Erro:

```text
AES usa números primos.
```

Correção:

```text
AES = simétrico, blocos/matrizes.
RSA = assimétrico, números primos.
```

---

## 2. Pensar que todo IoT usa criptografia

Errado.

O professor avisou que muitos dispositivos embebidos podem comunicar sem proteção adequada.

---

## 3. Pensar que assinatura digital serve para esconder conteúdo

Assinatura digital serve principalmente para provar autoria e integridade.

Encriptação serve para esconder conteúdo.

---

## 4. Pensar que sistemas embebidos são só ESP32

Nesta cadeira, sistema embebido inclui também:

* câmaras;
* TVs;
* contadores;
* dispositivos comerciais conectados.

---

## 5. Ignorar gestão de chaves

Mesmo com bom algoritmo, a segurança falha se:

* a chave for exposta;
* a chave privada for copiada;
* o arranque do dispositivo revelar segredos;
* houver password fraca ou de fábrica.
