/* Scrivi il codice sorgente di un prg in cui:
_il processo PADRE
_visualizza il proprio PID
_genera 4 figli: F1, F2, F3, F4
_genera 2 numeri interi random, n1, n2
 compresi tra 1 e 20
necessariamente diversi tra loro
_visualizza n1 ed n2:
  a prescindere dal valore di n1 ed n2,
  F2 dovrà dormire per un numero di secondi pari a n1 e
  restituire al padre un numero n2_dim intero compreso tra 2 e 6 estremi compresi;
  F3  dovrà dormire per un numero di secondi pari a n2 e
  restituire al padre un numero n3_dim intero compreso tra 2 e 10 estremi inclusi;
  non si sa chi dormirà di meno o di più ossia
  non si sa chi tra F2 ed F3 terminerà per primo.
_solo dopo avere generato entrambi (sia F2 e sia F3),
   attende la loro terminazione:
il numero intero restituito da F2 rappresenterà la dimensione dim  del vettore che F1 dovrà generare
_per ciascun figlio, il padre visualizza il proprio PID e il PID del proprio figlio

CIASCUN FIGLIO deve:
identificrsi dicendo se è F1 o F2 o F3 o F4
_visualizzare il proprio PID e il PID del proprio padre

F1 deve:
_ generare il vettore v[ ] di numeri interi di dimensione dim fornito in ingresso dall'utente e compresi tra 1 e 10 estremi inclusi
_ calcolarne la somma (somma)

F4 deve:
_ calcolare il valore medio (media) dei numeri  fornito in ingresso dall'utente e memorizzati nel vettore e
_ restituirlo al padre

Il PADRE deve:
visualizzare il proprio PID e il valore restituitogli da F4
con un chiaro messaggio in cui precisa ciò che esso rappresenta:
"Sono il padre, il mio PID = ... , il valore medio dei numeri con cui hai popolato il vettore vale ..."
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX 20
#define MIN 1

int random()
{
    return rand() % (MAX - MIN);
}

int main(int argc, char *argv[])
{
    // Dichiarazione delle variabili
    pid_t p, f1, f2, f3, f4;
    int dim, n1, n2;

    printf("Inserisci la dimensione del vettore: ");
    scanf("%d\n", &dim);
    int vet[dim];

    f1 = fork();
    if (f1 > 0) // Padre
    {
        printf("Sono il padre, mio PID = %d\n", getpid());
    }
    else if (f1 == 0) // f1
    {
        
    }
    else
    {
        perror("Errore nella generazione del figlio!\n");
    }

    return 0;
}