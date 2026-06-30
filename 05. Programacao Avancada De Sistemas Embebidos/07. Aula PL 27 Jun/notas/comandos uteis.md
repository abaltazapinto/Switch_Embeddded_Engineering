# GDB essencial para PRASIE

Compilar com símbolos:
gcc -Wall -Wextra -g ficheiro.c -o programa -pthread

Abrir:
gdb --tui ./programa

Comandos:
break main
break worker
break producer
break consumer
run
next
continue
info threads
thread N
print variavel
bt
quit