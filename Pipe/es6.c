/* Il file.txt rappresenta le fatture dell’ultimo mese della ditta ProgrammatoriHero srl
e contiene 3 campi: codice, “pagato” o “insoluto”, l’importo

Si vuole realizzare un programma concorrente in linguaggio C che mostri a video l'importo totale delle fatture emesse.

Si usi la seguente procedura:
Si generi un processo figlio P1 che legge il file e lo manda al processo P2 il quale
estrapola la terza colonna del file, e la manda al processo P0.
Il processo P0 riceve quindi tutti gli importi, ne calcola il totale e lo mostra a video.

Note operative
Il processo P1 usi il comando cat per mostrare il contenuto del file e inviarlo a P2
Il processo P2 usi il comando: awk '{print $3}' per estrapolare la terza colonna
Il processo P2 deve inviare al processo P0 la terza colonna
Il processo P0 deve leggere in input tutti i valori e per ogni lettura deve incrementare la variabile accumulatore “totale”

Osservazione:
strncat(strimporto, &buffer[0], sizeof(buffer[0]))
Aggiunge in coda alla stringa strimporto il carattere buffer[0] la cui dimensione è sizeof(buffer[0])

Osservazione:
char *ptr;
double x = strtod(strimporto, &ptr);
strtod converte la stringa strimporto in double.

Osservazione:
strimporto[0] = '\0';
Pone in posizione 0 di una stringa il carattere terminatore, in questo modo si resetta a livello logico una stringa
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // Controllo argomenti
    if (argc != 2)
    {
        perror("Numero argomenti sbagliato!\n");
        exit(1);
    }

    // Dichiarazione variabili
    int p1p0[2], p2p1[2], pid;
    double tot = 0;
    char buffer[1], strimporto[100], *ptr;

    pipe(p1p0); // creo la pipe
    pid = fork();

    if (pid == 0)
    {
        close(p1p0[0]); // chiudo la lettura
        close(1); // redireziono stdout
        dup(p1p0[1]);
        close(p1p0[1]);

        execl("/bin/cat", "cat", argv[1], (char *)0);
        return -1;
    }

    pipe(p2p1); // creo la pipe
    pid = fork();
    if (pid == 0)
    {
        close(p1p0[1]); // chiudo la scrittura
        close(0); // redireziono stdin
        dup(p1p0[0]);
        close(p1p0[0]);

        close(p2p1[0]); // chiudo la lettura
        close(1); // redireziono stdout
        dup(p2p1[1]);
        close(p2p1[1]);

        execl("/bin/awk", "awk", "{print $3}", (char *)0);
        return -1;
    }

    close(p1p0[0]);
    close(p1p0[1]);
    close(p2p1[1]);

    while (read(p2p1[0], buffer, sizeof(buffer)) > 0)
    {
        strncat(strimporto, &buffer[0], sizeof(buffer[0]));
        if (buffer[0] == '\n')
        {
            printf("Importo: %s", strimporto);
            tot += strtod(strimporto, &ptr); // str to double
            strimporto[0] = '\0';
        }
    }

    close(p2p1[0]);
    printf("\nTotale: %.2f\n", tot);

    return 0;
}