/* Scrivere un programma concorrente che realizzi il seguente comando:

cat costituzione.txt | more
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Controllo argomenti
    if (argc != 2)
    {
        perror("Numero argomenti sbagliato!\n");
        exit(1);
    }

    // Dichiarazione variabili
    pid_t pid;
    int p1p0[2];

    // Creazione pipe
    pipe(p1p0);

    if (pipe(p1p0) == -1)
    {
        perror("Errore creazione pipe!\n");
        exit(2);
    }

    pid = fork(); // creo figlio

    if (pid == 0) // figlio
    {
        close(p1p0[0]); // chiudo lettura
        close(1);       // chiudo stdin per liberare uno spazio da assegnare alla dup
        dup(p1p0[1]);
        close(p1p0[1]);
        execl("/bin/cat", "cat", argv[1], (char *)0); // eseguo cat
        return -1;
    }

    pid = fork();

    if (pid == 0)
    {
        close(p1p0[1]); // chiudo scrittura
        close(0);       // chiudo stdout per liberare uno spazio da assegnare alla dup
        dup(p1p0[0]);
        close(p1p0[0]);
        execl("/bin/more", "more", (char *)0);
        return -1;
    }

    close(p1p0[0]); // chiudo lettura
    close(p1p0[1]); // chiudo scrittura
    wait(&pid);     // aspetto che i figli terminino
    wait(&pid);

    return 0;
}