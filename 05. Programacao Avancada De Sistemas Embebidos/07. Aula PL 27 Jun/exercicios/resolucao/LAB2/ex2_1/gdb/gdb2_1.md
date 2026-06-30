GDB Thread 3 está bloqueada em futex_wait.
No frame 4, essa thread corresponde ao worker(arg=0x1).
Logo: GDB Thread 3 = worker 1 bloqueado no pthread_mutex_lock().



Thread 3  = número interno do GDB
worker 1  = o id lógico do teu programa
$4 = 1    = quarto resultado impresso pelo GDB

