// PROCESS TREE

/* Scrivi il codice sorgente di un programma in
cui il processo padre P1 genera un vettore V[3] di
tre numeri interi casuali
appartenenti all'intervallo [0;5] estremi compresi.
Successivamente, P1 genera due processi figli:
P2 e P3.
P2 genera due figli, P4 e P5:
P4 calcola e visualizza il prodotto delle
componenti del vettore V[];
P5 calcola e visualizza la media delle
componenti del vettore V[] .
P3 visualizza le componenti del vettore V[],
genera un figlio P6 che calcola la somma delle
componenti di V[] e restituisce il risultato al padre P3 che la
visualizza.
La prima cosa che ciascun processo deve fare,
appena genera un processo figlio, è dichiararsi nel modo seguente:
"P1: mio PID=..., mio figlio P2 ha PID=...
La prima cosa che ciascun processo figlio deve
fare appena è stato generato,
è dichiararsi nel modo seguente:
"P2: mio PID=..., mio padre P1 ha PID=..."
Ogni volta che un processo visualizza qualcosa
sullo schermo deve dichiararsi nel modo seguente:
"P4: quello che P4 deve visualizzare"
"P5: quello che P4 deve visualizzare
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define DIM 3

int main(int argc, char *argv[])
{
    // Variables declaration
    pid_t p2, p3, p4, p5, p6;
    int V[3];
    double prod = 1.0, media, sum = 0;

    srand(time(NULL));
    for (int i = 0; i < DIM; i++)
    {
        V[i] = rand() % 6;
    }

    p2 = fork();
    if (p2 > 0)
    {
        printf("P1, mio PID = %d\n", getpid());
        p3 = fork();
        if (p3 == 0)
        {
            printf("P3, mio PID = %d, mio padre P1 ha PID = %d\n", getpid(), getppid());
            printf("P3: ARRAY:\n");
            for (int i = 0; i < DIM; i++)
            {
                printf("%d\n", V[i]);
            }
            p6 = fork();
            if (p6 == 0)
            {
                printf("P6, mio PID = %d, mio padre P3 ha PID = %d\n", getpid(), getppid());
                for (int i = 0; i < DIM; i++)
                {
                    sum += V[i];
                }
                exit(sum);
            }
            wait(&p6);
            sum = WEXITSTATUS(p6);
            printf("P3: SOMMA: %.2f\n", sum);
        }
    }
    else if (p2 == 0)
    {
        printf("P2, mio PID = %d, mio padre P1 ha PID = %d\n", getpid(), getppid());
        p4 = fork();
        if (p4 > 0)
        {
            p5 = fork();
            if (p5 == 0)
            {
                printf("P5, mio PID = %d, mio padre P2 ha PID = %d\n", getpid(), getppid());
                for (int i = 0; i < DIM; i++)
                {
                    sum += V[i];
                }
                media = sum / DIM;
                printf("P5: MEDIA: %.2f\n", media);
            }
        }
        if (p4 == 0)
        {
            printf("P4, mio PID = %d, mio padre P2 ha PID = %d\n", getpid(), getppid());
            for (int i = 0; i < DIM; i++)
            {
                prod *= V[i];
            }
            printf("P4: PRODOTTO: %.2f\n", prod);
        }
    }

    return 0;
}