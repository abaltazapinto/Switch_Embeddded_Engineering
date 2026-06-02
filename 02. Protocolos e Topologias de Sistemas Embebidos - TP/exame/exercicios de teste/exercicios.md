Agora um exercício igual, mas com outro prefixo:

    2002:01c2:0000:1400::/56

Dividir em:

    8 edifícios

Pergunta:

Prefixo por edifício = /?

Edifício 0 = ?
Edifício 1 = ?
Edifício 2 = ?
Edifício 3 = ?

# Minha resposta

dividir po 8 edificios

2^3 = 8 

56 + 3 = 59 

    salto

    0x100 / 8 = 0x 125

# prefixo por edificio

2002:01c2:0000:1400::/59
2002:01c2:0000:1525::/59
2002:01c2:0000:1650::/59
2002:01c2:0000:1775::/59
2002:01c2:0000:1900::/59
2002:01c2:0000:1a25::/59
2002:01c2:0000:1b50::/59
2002:01c2:0000:1c75::/59

| Divisão a partir de `/56` | Novo prefixo | Nº de blocos | Salto hex |
| ------------------------: | -----------: | -----------: | --------: |
|                  2 blocos |        `/57` |            2 |    `0x80` |
|                  4 blocos |        `/58` |            4 |    `0x40` |
|                  8 blocos |        `/59` |            8 |    `0x20` |
|                 16 blocos |        `/60` |           16 |    `0x10` |
|                 32 blocos |        `/61` |           32 |    `0x08` |
|                 64 blocos |        `/62` |           64 |    `0x04` |
|                128 blocos |        `/63` |          128 |    `0x02` |
|                256 blocos |        `/64` |          256 |    `0x01` |
