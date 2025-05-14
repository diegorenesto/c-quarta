/* Scrivi il codice sorgente di un prg che
Copia, carattere per carattere, il contenuto di un file già esistente
In un secondo file da creare.
I nomi dei file devono essere forniti in input dall’utente da tastiera
*/

#include <stdio.h>

int main(int argc, char *argv[])
{

    // Controllo argomenti
    if (argc != 3)
    {
        perror("Errore numero argomenti!\n");
        exit(1);
    }

    // Dichiarazione variabili
    FILE *fd, *fd2;
    char contenuto[256]; // Buffer per il contenuto del file

    // Apro il primo file in lettura
    fd = fopen(argv[1], "r");
    
    // Apro il secondo file in scrittura
    fd2 = fopen(argv[2], "w");
    
    // Leggo il contenuto del primo file e lo scrivo nel secondo file
    while (fgets(contenuto, sizeof(contenuto), fd) != NULL)
    {
        fputs(contenuto, fd2);
    }

    // Chiudo i file
    fclose(fd);
    fclose(fd2);

    return 0;
}