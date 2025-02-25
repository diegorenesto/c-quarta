/* Scrivere un programma in linguaggio C che legge da argv una serie di stringhe,
le ordina in senso crescente o decrescente in funzione del flag usato in argv[2].
Si utilizzi un algoritmo di ordinamento a scelta. Si scriva il risultato
sia a video che su un file il cui nome risiede in argv[1].

Esempio:
$ ./a.out file.txt --asc ciao a tutti
$ ./a.out file.txt --desc ciao a tutti
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

void ordina(int argc, char *argv[]) // ordinamento con bubble sort da argv[3]
{
    int i, j;
    char *temp;
    for (i = 1; i < argc; i++)
    {
        for (j = 3; j < (argc - i); j++)
        {
            if (strcmp("--asc", argv[2]) == 0)
            {
                if (strcmp(argv[j], argv[j + 1]) > 0)
                {
                    temp = argv[j];
                    argv[j] = argv[j + 1];
                    argv[j + 1] = temp;
                }
            }
            else if (strcmp("--desc", argv[2]) == 0)
            {
                if (strcmp(argv[j], argv[j + 1]) < 0)
                {
                    temp = argv[j];
                    argv[j] = argv[j + 1];
                    argv[j + 1] = temp;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Numero argomenti sbagliato\n");
        exit(0);
    }

    // Dichiarazione delle variabili
    int fd, i;

    ordina(argc, argv); // ordinamento delle stringhe da linea di comando
    fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644); // apertura di un file descriptor

    for (int i = 3; i < argc; i++)
    {
        write(fd, argv[i], strlen(argv[i])); // scrittura nel file fd 
        write(fd, "\n", strlen("\n"));

        write(1, argv[i], strlen(argv[i])); // scrittura a video
        write(1, "\n", strlen("\n"));
    }
    close(fd); // chiusura file fd

    return 0;
}
