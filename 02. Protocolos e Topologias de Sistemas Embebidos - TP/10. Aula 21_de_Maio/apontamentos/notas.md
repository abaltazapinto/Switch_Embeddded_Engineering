![alt text](image.png)

![alt text](image-1.png)

servico oferecido por UDP e servico sem seguranca a mensagem pode chegar ou nao chegar, enquanto no TCP sao confirmados, se algum segmento nao chegar ao destino ele e reenviado. O UDP define cabeca lho simples 

![alt text](image-2.png)

4 campos. 

em ingles chaman se PORT

O IP trata do enderecamento , dentro de uma maquina podemos ter uma aplicacao a comunicar ao mesmo tempo. Browsers admintem varios tabs ', podemos estar a carregar , 

aopplicacao a que se destina...

PORT em tcp e feita deum porto par aoutro porto, em UDP.. datagrama a plicacao A ou enderacemento B

- o checksum no udp e opcional
    sem checksum fica mais rapido mas probabiloidae de mkais kerros.

- o checksum e calculado com cabecalho... 
estes dados sxao usados 'para calcular checksu,.


![alt text](image-3.png)

PORTOS super importantes. varias apolicacoes a falar ao mesmo tempo. 

porto de orgiem e destido 16 bits, especificar asmdsadm mil portos

---

servico a escuta num porto, temos de identifivcart o porto onde queremos aceder. os servicos mais comuinsa, para nao temros de identifica r, umse ervico web comot estar instalaado no porto 80. IANA 

![alt text](image-4.png)

tem mais de mil portos, esta tabela esta disponvel para toda gente. As maquinas com tcp e udp tambem tem tabel adeste genero. 

/etc/services

![alt text](image-5.png)

wowowwo aprendi

![alt text](image-6.png)


NTP antes usava se no tempo do professor. 

era unidirecional, 

os portos que quisermos, por necessidade so cump[rir as normas quando vamos publicar coisas. 

![alt text](image-7.png)

UDP sobre IP e 65 k

![alt text](image-8.png)

TCP e mais complexo que UDP adiciona fiabilidade e ligacoes establecidas. 
tcpo encarregase de implementar fiabilidade. 

TCP numerar os pacotes , assim sabe se onde comeca e acaba !! 

![alt text](image-9.png)

![alt text](image-10.png)

cabecalho tcp e mais complexo e grande !!!!

window size serve para o controlo de fluxo, 

este campo tem 0- ou mais palavras de 32 bits

![alt text](image-11.png)

existe um campo header length. apontador para dados urgentes ajuda para saber onde comeca os dados. Para especificar o tamanho maximo permitido. 

perceber este mecanismo ilustrado

![alt text](image-12.png)

![alt text](image-13.png)

![alt text](image-14.png)

segmento tcp sem dados. 

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

Flags de FIN. tem de ser confirmada tem decontinuar a aceitar dados ate quue ambas tem manifestado o interesse a encerrar.

![alt text](image-18.png)

![alt text](image-19.png)

quando os extremos nao concordam e uma situacao half close. 

as maquina stem de garantir que contiiuhnuam a receber dados. 

rsh bsdi sort < datafile permite abrir maquinas remotaments>

rsh e antecessor do ssh , e um rsh seguro, se tiver um servidor rshell, rsh nao ha trocas de chaves, posso usar o shell noutra maquina, ou posso executar comandos, 
requisitoos

    - autenticacao aberto
    - estamos admitir que exite mecanismo de autenticacao configurado. 

    simbolo menor e um redirecionamento de entrada , entao o sort vai ordenar ....

    terminal remoto...

    implementcao rshel vai establecer uma ligacao TCP, 

    ![alt text](image-20.png)

    ![alt text](image-21.png)

    ![alt text](image-22.png)


![alt text](image-23.png)


# garantia de entrega


# controlo de fluxo nao sobreegue o receptor 

![alt text](image-25.png)

fala me de # controlo de fluxo nao sobreegue o receptor , pouca capacidade de recepcao,mo tcp encarrega se de controlar fluxo de dos, e anunciem a capacidde de receber , maquina esqiuerda boa e rapida e direita ma e lenta, overflow, buffer de recepccao pequeno


## Ação — 1 passo

Olha para esta parte da imagem:

```text id="k4vov7"
ACK = 4096   WIN = 0
```

e tenta interpretar:

```text id="mb22ng"
“o recetor está cheio”
```

## Objetivo

Compreender a ideia central do **controlo de fluxo TCP**:

```text id="g5md9w"
não deixar o emissor rápido sobrecarregar o recetor lento
```

## Como pensar

Imagina:

| Máquina esquerda   | Máquina direita     |
| ------------------ | ------------------- |
| PC muito rápido 🚀 | Raspberry lento 🐢  |
| SSD/RAM grande     | buffer pequeno      |
| envia muitos dados | processa lentamente |

Se o emissor continuar a enviar dados demasiado rápido:

```text id="rr2bze"
overflow do buffer de receção
```

Os dados começam a perder-se.

Então o TCP faz algo inteligente:

```text id="xpy5wj"
o recetor anuncia quanto espaço ainda tem
```

Isso é a:

```text id="fjw6q1"
TCP Receive Window
```

ou:

```text id="4v3o0q"
WIN
```

na imagem.

---

### Interpretação da figura

Primeiro:

```text id="5v6mjt"
WIN = 2048
```

quer dizer:

```text id="kz32xf"
“ainda podes enviar 2 KB”
```

Depois o buffer enche:

```text id="q7wl5f"
WIN = 0
```

agora o recetor está a dizer:

```text id="y7e7wb"
“PARA. Não consigo receber mais.”
```

Então:

```text id="ltp44q"
Sender is blocked
```

O emissor espera.

Só quando a aplicação da direita lê dados do buffer:

```text id="6m0w6k"
Application reads 2K
```

é que o TCP volta a anunciar espaço:

```text id="v11k6y"
WIN = 2048
```

e o envio continua.

---

## Ideia crítica de engenharia

TCP não controla apenas:

* erros,
* retransmissões,
* ordem dos pacotes.

Também controla:

```text id="sv4on2"
velocidade de transmissão
```

adaptando-se ao recetor.

Isto é essencial em:

* embedded systems,
* IoT,
* Raspberry Pi,
* microcontroladores,
* redes lentas,
* UART over TCP bridges,
* Wi-Fi congestionado.

## Pitfalls

* Confundir **controlo de fluxo** com **controlo de congestionamento**.
* `WIN=0` não significa falha; significa “espera”.
* Buffers pequenos aumentam bloqueios.
* Se a aplicação não ler do socket, o buffer TCP enche.

## Alternativas / tradeoffs

| Estratégia     | Vantagem         | Problema              |
| -------------- | ---------------- | --------------------- |
| Buffer grande  | maior throughput | mais RAM              |
| Buffer pequeno | menos memória    | mais bloqueios        |
| UDP            | baixa latência   | sem controlo de fluxo |
| TCP            | fiável           | mais overhead         |

## Pergunta de decisão

Queres agora perceber:

1. diferença entre **flow control** e **congestion control**,
   ou
2. como isto funciona internamente com buffers no kernel Linux/socket API?


---

![alt text](image-26.png)

![alt text](image-27.png)

algoritmo d enaghel

