/*Scrivi il codice sorgente di un prg in cui
   il processo padre P genera due figli: F1 e F2.

   A F1 assegna un tempo t di sleep(t) (ritardo) 2 secondi;
   F1 deve restituire al padre P il numero 2.
   A F2 assegna un tempo t di sleep(t) (ritardo) 4 secondi;
   F2 deve restituire al padre P il numero 4.

   Padre P deve attendere la terminazione del figlio che dorme di piÃ¹, ossia F2, e
   deve scrivere quanti secondi ha dormito tale figlio.

   La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
   Ã¨ dichiararsi nel modo seguente:
   "P: mio PID=..., mio figlio F1 ha PID=...
   La prima cosa che ciascun processo figlio deve fare appena Ã¨ stato generato,
   Ã¨ dichiararsi nel modo seguente:
   "F1: mio PID=..., mio padre P ha PID=..."

   Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
   "P: quello che P deve visualizzare"
   "..."
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Variables Declaration
    pid_t f1, f2;
    int son, heung_min;

    f1 = fork();
    if (f1 > 0) // Parent
    {
        printf("P = %d, my son F1 = %d\n", getpid(), f1);
        f2 = fork();
        if (f2 > 0)
        {
            printf("P = %d, my son F2 = %d\n", getpid(), f2);
        }
        else if (f2 == 0) // F2
        {
            wait(&f1);
            printf("F2 = %d, my parent has PID = %d\n", getpid(), getppid());
            printf("I sleep 4 secs\n");
            sleep(4);
            exit(4);
        }
        else
        {
            printf("Error: son generation wrong\n");
        }
    }
    else if (f1 == 0) // F1
    {
        printf("F1 = %d, my parent has PID = %d\n", getpid(), getppid());
        printf("I sleep 2 secs\n");
        sleep(2);
        exit(2);
    }
    else
    {
        printf("Error: son generation wrong\n");
    }

    son = waitpid(f1, &f1, 0);
    printf("My son %d has slept for %d seconds\n", son, WEXITSTATUS(f1));
    heung_min = waitpid(f2, &f2, 0);
    printf("My son %d has slept for %d seconds\n", heung_min, WEXITSTATUS(f2));
    return 0;
}