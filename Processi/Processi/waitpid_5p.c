#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // Dichiarazione variabili
    pid_t p1, p2, p3, p4, p5;
    int arr[5];
    int sum = 0, min, max;

    // Creazione processo figlio P2
    p1 = getpid();
    p2 = fork();

    if (p2 > 0)
    {
        waitpid(p2, &sum, 0);
        printf("P1 mio PID = %d: la somma dei numeri inseriti da P2 è %d\n", getpid(), WEXITSTATUS(sum));
        // Creazione processo figlio P3
        p3 = fork();
        if (p3 > 0)
        {
        }
        else if (p3 == 0) // P3
        {
            printf("P3, mio PID = %d, mio padre P1 ha PID = %d\n", getpid(), p1);
            min = arr[0];
            for (int i = 1; i < 5; i++)
            {
                if (arr[i] < min)
                {
                    min = arr[i];
                }
            }

            waitpid(p3, &min, 0);
            exit(min);
        }
        else
        {
            perror("Errore nella fork di P3");
            exit(1);
        }
    }
    else if (p2 == 0) // P2
    {
        printf("P2, mio PID = %d, mio padre P1 ha PID = %d\n", getpid(), p1);
        printf("Inserisci 5 numeri interi: ");
        // Popolamento del vettore
        for (int i = 0; i < 5; i++)
        {
            scanf("%d", &arr[i]);
        }
        printf("P2 mio PID = %d: ", getpid());
        // Visualizzazione del contenuto del vettore
        for (int i = 0; i < 5; i++)
        {
            printf("%d ", arr[i]);
            sum += arr[i];
        }
        waitpid(p3, &min, 0);
        printf("P2 mio PID = %d: il valore minimo tra i numeri inseriti da P2 è %d\n", getpid(), WEXITSTATUS(min));
        // Creazione processo figlio P4
        p4 = fork();
        if (p4 > 0)
        {
        }
        else if (p4 == 0) // P4
        {
            printf("P4, mio PID = %d, mio padre P2 ha PID = %d\n", getpid(), p2);
            max = arr[0];
            for (int i = 1; i < 5; i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                }
            }

            exit(max);
        }
        else
        {
            perror("Errore nella fork di P4");
            exit(1);
        }
        waitpid(p4, &max, 0);
        printf("P2 mio PID = %d: il valore massimo tra i numeri inseriti da P2 è %d\n", getpid(), WEXITSTATUS(max));
        // Creazione processo figlio P5
        p5 = fork();
        if (p5 > 0)
        {
        }
        else if (p5 == 0) // P5
        {
            printf("P5, mio PID = %d, mio padre P2 ha PID = %d\n", getpid(), p2);
            int media = 0;
            for (int i = 0; i < 5; i++)
            {
                media += arr[i];
            }
            media /= 5;
            exit(media);
        }
        else
        {
            perror("Errore nella fork di P5");
            exit(1);
        }
        waitpid(p5, &sum, 0);
        printf("P2 mio PID = %d: il valore medio tra i numeri inseriti da P2 è %d\n", getpid(), WEXITSTATUS(sum));
        exit(sum);
    }
    else
    {
        perror("Errore nella fork di P2");
        exit(1);
    }

    return 0;
}

/* Scrivi il codice
sorgente di un programma in cui

il processo padre P1

_ genera un processo
figlio P2

P2

_ genera un vettore v[] di 5 numeri interi, forniti in input dall’utente >> N.B.
    Fare attenzione!!!

_ visualizza il
contenuto del vettore

_ calcola la somma dei
numeri del vettore che, però, verrà visualizzata dal padre P1

_ successivamente,
genera il processo figlio P3

P3 calcola il valore
minimo tra i numeri del vettore

P2

_ attende la terminazione
di P3 e visualizza il valore minimo

_ successivamente,
genera il processo figlio P4

P4 calcola il valore
massimo tra i numeri del vettore

P2

_ attende la terminazione
di P4 e visualizza il valore massimo

_ successivamente,
genera il processo figlio P5

P5 calcola il valore medio
tra i numeri del vettore

P2

_ attende la terminazione
di P5 e visualizza il valore medio

\La prima cosa che
ciascun processo deve fare, appena genera un processo figlio, è dichiararsi nel
modo seguente:

"P1: mio PID=...,
mio figlio P2 ha PID=...

La prima cosa che
ciascun processo figlio deve fare appena è stato generato,

è dichiararsi nel modo
seguente:

"P2: mio PID=...,
mio padre P1 ha PID=..."

Ogni volta che un
processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:

"P1 mio PID=...:
quello che P1 deve visualizzare"

"Pn mio PID=...:
quello che Pn deve visualizzare"
*/