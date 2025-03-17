/*Si vuole realizzare in linguaggio C un software monoprocesso che implementi il seguente comando:
$ cat file1.txt file2.txt file3.txt /tmp/file4.txt | grep “c”

Dove file[N].txt con N maggiore uguale a 1 sono una serie di files scelti dall'utente e il carattere
"c" è a scopo esemplificativo e potrebbe essere qualsiasi carattere.

Si utilizzino le system call al fine di leggere tutti i file di testo e, per ogni file, ricercare il carattere.
Al termine dell’esecuzione il software dovrà mostrare a video il numero di occorrenze trovate nei files e
dovrà contemporaneamente scrivere l’output su un file di testo il cui path sarà letto da argv.

Esempio:
$ ./a.out file1.txt file2.txt file3.txt k occorrenze.txt
$ Il carattere k compare 10 volte nei files: file1.txt, file2.txt, file3.txt
$ cat occorrenze.txt
$ Il carattere k compare 10 volte nei files: file1.txt, file2.txt, file3.txt

Esempio:
$ ./a.out file1.txt file2.txt file3.txt /tmp/file3.txt q /tmp/occorrenze.txt                                                                     
$ Il carattere q compare 18 volte nei files: file1.txt file2.txt file3.txt /tmp/file3.txt 
$ cat /tmp/occorrenze.txt                                                                                             
$ Il carattere q compare 18 volte nei files: file1.txt file2.txt file3.txt /tmp/file3.txt


Osservazioni:
essendo il software monoprocesso non è necessario usare le pipe
prestare attenzione all’uso corretto di argv
si ricorda che il software deve funzionare per un numero arbitrario di files di input.
i percorsi dei files possono essere sia assoluti che relativi 
 

Suggerimento:
Per facilitare la ricerca è possibile leggere un singolo carattere per volta usando la funzione read.
Utilizzare la funzione strcat per concatenare due stringhe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int calcola_files(int argc, char *argv[])
{
    int n = 0;
    for (int i = 1; i < argc - 2; i++)
    {
        n = n + strlen(argv[i]) + 1;
    }
    return n;
}

void componi_stringa_files(int argc, char *argv[], char str[])
{
    str[0] = '\0'; // resetto l'array cancellando tutto il contenuto
    for (int i = 1; i < argc - 2; i++)
    {
        strcat(str, argv[i]);
        strcat(str, " ");
    }
    strcat(str, "\n");
}

int main(int argc, char *argv[])
{

    if (argc < 5)
    {
        printf("Numero argomenti sbagliato\n");
        exit(1);
    }

    // Dichiarazione delle variabili
    int fd, cont = 0, dim = calcola_files(argc, argv);
    char carattere, caratterix[80], stringa_files[dim];

    for (int i = 1; i < argc - 2; i++)
    {
        fd = open(argv[i], O_RDONLY);

        while (read(fd, &carattere, sizeof(carattere) > 0)) // se legge qualcosa ritorna i byte dei caratteri letti
        {
            if (carattere == argv[argc - 2][0]) // carattere inserito da argv
            {
                cont++;
            }
        }

        close(fd);
    }
    componi_stringa_files(argc, argv, stringa_files);

    sprintf(caratterix, "Il carattere %s compare %d volte nei files: %s\n", argv[argc - 2], cont, stringa_files);

    write(1, caratterix, strlen(caratterix));
    fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    write(fd, caratterix, strlen(caratterix));

    close(fd);

    return 0;
}