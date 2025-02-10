/*Scrivere un programma in linguaggio C che usa il comando
della shell rm per eliminare tutti files presenti
nell'intervallo [argv[1], argv[argc-1]]

esempio:
$ ./a.out /tmp/1.txt /tmp/3.txt /tmp/2.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        perror("Numero argomenti sbagliato!\n");
        exit(1);
    }

    execl("/usr/bin/rm", "rm", argv[1], argv[argc - 1], NULL);

    return 0;
}