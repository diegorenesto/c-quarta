/* Leggi il file numeri.txt già esistente,
composto da una sequenza di numeri di una cifra separati da uno spazio.
Scrivi due file, pari.txt e dispari.txt
nei quali inserisci, rispettivamente,
i numeri letti a seconda del loro valore pari o dispari.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    // Controllo argomenti
    if(argc != 1)
    {
        perror("Errore numero argomenti!\n");
        exit(1);
    }

    // Dichiarazione variabili
    FILE *fd, *pari, *dispari;
    int numero;

    fd = fopen("numeri.txt", "r");


    // Apro il file pari in scrittura
    pari = fopen("pari.txt", "w");
    if(pari == NULL)
    {
        perror("Errore nell'apertura del file di output pari");
        fclose(fd);
        exit(1);
    }

    // Apro il file dispari in scrittura
    dispari = fopen("dispari.txt", "w");
    if(dispari == NULL)
    {
        perror("Errore nell'apertura del file di output dispari");
        fclose(fd);
        fclose(pari);
        exit(1);
    }


    // Leggo il contenuto del file e lo scrivo nei file pari e dispari
    while(fscanf(fd, "%d", &numero) != EOF)
    {
        if(numero % 2 == 0)
        {
            fprintf(pari, "%d ", numero);
        }
        else
        {
            fprintf(dispari, "%d ", numero);
        }
    }

    // Chiudo i file
    fclose(fd);
    fclose(pari);
    fclose(dispari);

    return 0;
}