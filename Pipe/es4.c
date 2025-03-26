/* Si scriva un’applicazione concorrente che presenti la seguente interfaccia:

cercaStringhe FileIn.txt

dove FileIn.txt è un nome assoluto di file.

L’applicazione deve contare il numero di volte in cui un insieme di stringhe
che l’utente inserisce da terminale (una alla volta) compaiono all’interno
del file passato come parametro in argv[1].
L’applicazione termina quando l’utente inserisce la stringa “fine”.

L’applicazione deve visualizzare il numero di volte in cui ogni stringa
compare nel file e anche, al termine dell’esecuzione, il numero totale di
stringhe trovate nel file.

L'applicazione dovrà tenere conto dell'eventuale molteplicità di una parola
dentro alla stessa stringa, per fare questo si consiglia di invocare grep
con il flag -ow e redirezionare il suo output in wc (invocato con il flag -l).
*/

// A DIFFERENZA DELL'ESERCIZIO 3 TIENE IL CONTO ANCHE DELLE PAROLA RIPETUTE ALL'INTERNO DELLA STESSA RIGA

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
    int p1p0[2], p2p0[2], pid, conttt = 0;
    char parola[100], cont[1000];

    while (1)
    {
        printf("Che parola vuoi cercare?\n");
        scanf("%s", parola);

        if (strcmp(parola, "fine") == 0)
        {
            close(p1p0[0]);
            close(p1p0[1]);
            close(p2p0[0]);
            close(p2p0[1]);
            printf("Numero di parole trovate: %d\n", conttt);
            exit(1);
        }

        pipe(p1p0); // creo la prima pipe
        pid = fork();

        if (pid == 0)
        {
            close(p1p0[0]); // chiudo la lettura
            close(1);       // chiudo lo stdout e ci metto la pipe
            dup(p1p0[1]);
            close(p1p0[1]);

            execl("/bin/grep", "grep", "-ow", parola, argv[1], (char *)0);
            return -1;
        }

        pipe(p2p0); // creo la seconda pipe
        pid = fork();

        if (pid == 0)
        {
            close(p1p0[1]); // chiudo la scrittura
            close(0);       // chiudo lo stdin e ci metto la pipe
            dup(p1p0[0]);
            close(p1p0[0]);

            close(p2p0[0]); // chiudo la lettura
            close(1);       // chiudo lo stdout e ci metto la seconda pipe
            dup(p2p0[1]);
            close(p2p0[1]);

            execl("/usr/bin/wc", "wc", "-l", (char *)0);
            return -1;
        }

        close(p1p0[0]);
        close(p1p0[1]);
        close(p2p0[1]);
        // non chiudo p2p0[0] perchè devo leggere

        read(p2p0[0], cont, sizeof(cont)); // leggo il numero di occorrenze e lo salvo in cont
        close(p2p0[0]);
        printf("Il file contiene %d '%s'\n", atoi(cont), parola);
        conttt += atoi(cont); // incremento il contatore totale
    }
    /*
    VANNO CHIUSE ALL'INTERNO DEL CICLO, per via del fatto che ogni iterazione crea nuove pipe
        close(p1p0[0]);
        close(p1p0[1]);
        close(p2p0[0]);
        close(p2p0[1]);
    */
    return 0;
}