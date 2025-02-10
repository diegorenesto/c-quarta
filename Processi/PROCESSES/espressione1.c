/* Scrivi il codice sorgente di un prg in cui
   il processo padre P genera due processi figli: F1 e F2.
   F1 somma 1+2;
   F2 somma 3+4.
   Entrambi restituiscono al processo padre P il risultato ottenuto dall'operazione compiuta.
   Padre P somma tra loro i risultati che i due figli gli hanno restituito e
   visalizza il valore di tale somma.

   La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
   Ã¨ dichiararsi nel modo seguente:
   "P: mio PID=..., mio figlio F1 ha PID=...
   La prima cosa che ciascun processo figlio deve fare appena Ã¨ stato generato,
   Ã¨ dichiararsi nel modo seguente:
   "F1: mio PID=..., mio padre P ha PID=..."

   Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
   "P: quello che P deve visualizzare"
*/

#include <stdio.h>
#include <stdl  ib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Variables declaration
    pid_t f1, f2;
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
    int sum = 0, sum2 = 0;

    f1 = fork();
    if (f1 == 0) // F1
    {
        printf("F1, PID = %d\n", getpid());
        sum = n1 + n2;
        exit(sum);
    }
    if (f1 > 0) // Parent
    {
        f2 = fork();
        if (f2 == 0) // F2
        {
            printf("F2, PID = %d\n", getpid());
            sum2 = n3 + n4;
            exit(sum2);
        }
        wait(&f1);
        sum = WEXITSTATUS(f1);
        wait(&f2);
        sum2 = WEXITSTATUS(f2);
        printf("P: n1 + n2 = %d, n3 + n4 = %d", sum, sum2);
    }

    return 0;
}