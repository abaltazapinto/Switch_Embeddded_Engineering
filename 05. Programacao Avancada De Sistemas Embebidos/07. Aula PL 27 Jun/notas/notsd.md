Regra:
Se uma thread verifica uma condição partilhada e a condição ainda não está pronta,
deve libertar o mutex antes de dormir, esperar ou fazer continue.

Errado:
lock(mutex);
if (condition_not_ready) {
    usleep(1000);   // mau: dorme com o mutex preso
}
unlock(mutex);

Correto:
lock(mutex);
if (condition_not_ready) {
    unlock(mutex);
    usleep(1000);
    continue;
}
// critical section
unlock(mutex);

