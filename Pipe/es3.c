/* Si scriva un’applicazione concorrente che presenti la seguente interfaccia:

cercaStringhe FileIn

dove FileIn è un nome assoluto di file.

L’applicazione deve contare il numero di volte in cui un insieme di stringhe
che l’utente inserisce da terminale (una alla volta) compaiono all’interno
del file passato come parametro in argv[1].
Se in una riga del file una parola compare più volte, al fine del conteggio,
considerare solamente la prima occorrenza.
L’applicazione termina quando l’utente inserisce la stringa “fine”.
L’applicazione deve visualizzare il numero di volte in cui ogni stringa
compare nel file e anche, al termine dell’esecuzione, il numero totale di
stringhe trovate nel file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

    // Dichiarazione variabili
    int p1p0[2], pid, conttt = 0;
    char parola[100], cont[1000];

    pipe(p1p0); // Creo la pipe

    while (1)
    {
        printf("Che parola vuoi cercare:\n");
        scanf("%s", parola);

        if (strcmp(parola, "fine") == 0) // se l'utente scrive fine termina il programma
        {
            close(p1p0[1]);
            close(p1p0[0]);
            printf("Numero di parole trovate: %s\n", cont);
            exit(1);
        }

        pid = fork();

        if (pid == 0)
        {
            close(p1p0[0]);
            close(1); // chiudo lo stdout per liberare uno spazio
            dup(p1p0[1]);
            close(p1p0[1]);

            execl("/bin/grep", "grep", "-c", parola, argv[1], (char *)0); // conto le occorrenze della parola
            return -1;
        }
        read(p1p0[0], cont, sizeof(cont));
        printf("Il file ha %d '%s'\n", atoi(cont), parola); // stampo il numero di occorrenze
        conttt += atoi(cont);                               // incremento il contatore totale
    }

    return 0;
}