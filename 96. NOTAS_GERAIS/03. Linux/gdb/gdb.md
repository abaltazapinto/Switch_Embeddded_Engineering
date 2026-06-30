## Ação (1 passo) ⚡

Copia isto no terminal para guardar uma folha rápida em `gdb.md`:

````bash
cat > gdb.md <<'EOF'
# GDB / TUI — comandos úteis rápidos

## Compilar para debug

```bash
gcc -g -O0 -Wall -Wextra -pthread ficheiro.c -o programa
````

## Abrir GDB normal

```bash
gdb ./programa
```

## Abrir GDB com TUI

```bash
gdb -tui ./programa
```

---

## Comandos básicos dentro do GDB

```gdb
break main          # breakpoint no main
break nome_funcao   # breakpoint numa função
break ficheiro.c:25 # breakpoint numa linha
run                 # iniciar programa
next                # próxima linha sem entrar em funções
step                # entra dentro da função
continue            # continua até ao próximo breakpoint
finish              # sai da função atual
quit                # sair do GDB
```

---

## Ver variáveis

```gdb
print counter       # mostra valor da variável
print &counter      # mostra endereço
display counter     # mostra sempre que o programa pára
undisplay           # remove displays
info locals         # variáveis locais
info args           # argumentos da função
```

---

## Threads

```gdb
info threads        # lista threads
thread 1            # muda para thread 1
thread 2            # muda para thread 2
thread apply all bt # backtrace de todas as threads
```

---

## Backtrace / stack

```gdb
bt                  # mostra cadeia de chamadas
frame 0             # frame atual
frame 1             # frame anterior
up                  # sobe na stack
down                # desce na stack
```

---

## TUI

```gdb
layout src          # mostra código C
layout asm          # mostra assembly
layout split        # C + assembly
layout regs         # registos
tui disable         # desliga TUI
tui enable          # liga TUI
```

Atalhos TUI:

```text
Ctrl+x a            # liga/desliga TUI
Ctrl+x 1            # uma janela
Ctrl+x 2            # duas janelas
Ctrl+l              # redesenhar ecrã se ficar bugado
```

---

## Race condition / mutex checklist

```gdb
break producer
break consumer
run
info threads
print counter
next
continue
```

Pergunta mental:

* Quem escreve a variável partilhada?
* Quem lê?
* A leitura/escrita está dentro do mutex?
* O valor muda fora da região crítica?
  EOF

````

## Objetivo

Ficas com um ficheiro `gdb.md` pronto para Git/consulta rápida durante a aula.

## Pitfall principal

Não escrevas `tui` no terminal Linux. O correto é:

```bash
gdb -tui ./programa
````
