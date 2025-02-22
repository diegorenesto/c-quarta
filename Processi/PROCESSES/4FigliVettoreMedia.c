#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// Genera un numero casuale tra min e max (inclusi)
int _random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int main()
{
    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    pid_t f1, f2, f3, f4;
    int n1, n2, dim, n2_dim, n3_dim;

    printf("Sono il padre, mio PID = %d\n", getpid());

    // Genera due numeri casuali diversi tra 1 e 20
    do
    {
        n1 = _random(1, 20);
        n2 = _random(1, 20);
    } while (n1 == n2);

    printf("Il padre ha generato n1 = %d, n2 = %d\n", n1, n2);

    f2 = fork();
    if (f2 == 0)
    { // F2
        printf("Sono F2, mio PID = %d, mio padre = %d\n", getpid(), getppid());
        sleep(n1);
        n2_dim = _random(2, 6);
        exit(n2_dim);
    }

    f3 = fork();
    if (f3 == 0)
    { // F3
        printf("Sono F3, mio PID = %d, mio padre = %d\n", getpid(), getppid());
        sleep(n2);
        n3_dim = _random(2, 10);
        exit(n3_dim);
    }

    waitpid(f2, &n2_dim, 0); // attende la terminazione di F2 e F3
    n2_dim = WEXITSTATUS(n2_dim);
    printf("Il padre ha ricevuto da F2 la dimensione del vettore: %d\n", n2_dim);

    waitpid(f3, &n3_dim, 0);
    n3_dim = WEXITSTATUS(n3_dim);

    // generazione del figlio F1 dopo aver ricevuto dim da F2
    f1 = fork();
    if (f1 == 0)
    { // F1
        printf("Sono F1, mio PID = %d, mio padre = %d\n", getpid(), getppid());
        int vet[n2_dim];
        int somma = 0;

        for (int i = 0; i < n2_dim; i++)
        {
            vet[i] = _random(1, 10);
            somma += vet[i];
        }

        printf("F1 ha generato un vettore di dimensione %d e la sua somma vale %d\n", n2_dim, somma);
        exit(0);
    }
    wait(NULL);

    // Generazione del figlio F4
    f4 = fork();
    if (f4 == 0)
    { // Figlio F4
        printf("Sono F4, mio PID = %d, mio padre = %d\n", getpid(), getppid());
        float media = (float)n3_dim / n2_dim;
        exit((int)media);
    }

    int media;
    waitpid(f4, &media, 0);
    media = WEXITSTATUS(media);

    printf("Sono il padre, mio PID = %d, il valore medio dei numeri con cui hai popolato il vettore vale %d\n", getpid(), media);

    return 0;
}