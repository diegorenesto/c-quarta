/* Un’applicazione multiprocesso in C deve presentare la seguente interfaccia:
controlloFatture nomeFileFatture
dove nomeFileFatture è un nome assoluto di file.

A questo fine, l’addetto dell’azienda deve verificare, sul file passato
come parametro, se un cliente ha ancora delle fatture in sospeso oppure se
le ha pagate tutte.

Nel file passato come parametro sono memorizzate tutte le fatture, una per
ogni riga. Ogni riga è composta dal nome del cliente (un codice di 5 caratteri
alfanumerico che identifica univocamente ogni cliente), da un campo che
contiene la stringa “pagato” per le fatture saldate oppure “insoluto”
per quelle ancora insolute, più altri campi con altre informazioni.

L’addetto dell’azienda inserisce a terminale il codice dei clienti (uno alla
volta) di cui vuole controllare lo stato dei pagamenti. Per ogni cliente
inserito, l’applicazione deve visualizzare il nome del cliente stesso e il
numero di fatture di tale cliente che risultano ancora da pagare.

Quando l’applicazione termina,a causa dell’inserimento della stringa “esci”,
il programma deve visualizzare il numero totale di richieste di servizio
eseguite fino a quel momento.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Controllo argomenti
    if (argc != 2)
    {
        perror("Numero argomenti sbagliato!\n");
        exit(1);
    }

    // Dichiarazione variabili
    int p1p0[2], pid, totRichieste = 0;
    char codice[12], stringa[1000];

    pipe(p1p0); // creo la pipe

    while (1)
    {
        printf("Inserisci il codice:\n");
        scanf("%s", codice);

        if (strcmp(codice, "esci") == 0)
        {
            close(p1p0[0]);
            close(p1p0[1]);
            printf("Numero totale di richieste eseguite: %d\n", totRichieste);
            exit(1);
        }

        pid = fork();
        if (pid == 0)
        {
            close(p1p0[0]); // chiudo la lettura
            close(1);       // chiudo lo stdout e ci metto la pipe
            dup(p1p0[1]);
            close(p1p0[1]);

            execl("/bin/grep", "grep", "-c", strcat(codice, " insoluto"), argv[1], (char *)0);
            return -1;
        }

        read(p1p0[0], stringa, sizeof(stringa));
        printf("Numero di fatture insolute per il cliente %s: %d\n", codice, atoi(stringa));
        totRichieste++;

        if (pid < 0)
        {
            perror("Errore nella fork!\n");
            exit(0);
        }
    }

    return 0;
}