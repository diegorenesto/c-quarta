// RENESTO DIEGO 4F 15/05/2025 FILA A

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define DIM 256
#define DIM_FIN 1000

int main(int argc, char *argv[])
{
    // Controllo argomenti
    if (argc != 1)
    {
        perror("Errore numero argomenti");
        exit(1);
    }

    // Dichiarazione variabili
    FILE *file, *verificata, *report;
    int F1, F2;
    char stringa[DIM], stringa_finale[DIM_FIN];

    // Genero il primo processo F1
    F1 = fork();
    if (F1 == 0) // F1
    {
        // Genero il secondo processo F2
        F2 = fork();
        if (F2 == 0) // F2
        {
            // Faccio inserire una stringa all'utente
            printf("Inserisci una frase (massimo 256 caratteri): ");
            fgets(stringa, DIM, stdin);

            // Apro il file in modalita' scrittura
            file = fopen("frase.txt", "w");
            if (file == NULL)
            {
                perror("Errore apertura file");
                exit(1);
            }

            fputs(stringa, file); // scrivo la stringa sul file
            fclose(file);         // chiudo il file

            exit(0);
        }
        else if (F2 > 0)
        {
        }
        else // errore
        {
            perror("Errore generazione secondo processo!\n");
            exit(1);
        }

        // Aspetto che il processo termini
        wait(NULL);                                      // aspetto che il processo termini
        verificata = fopen("frase_verificata.txt", "a"); // apro verificata.txt in append

        file = fopen("frase.txt", "r"); // apro il file in modalità di lettura
        // Salvo e scrivo sul file
        fgets(stringa, DIM, file);
        fputs(stringa, verificata);

        fputs("Verificata", verificata); // appendo la stringa "Verificata"
        fclose(verificata);              // chiudo il file
    }
    else if (F1 > 0) // Padre
    {
        // aspetto che il processo termini
        wait(NULL);

        // Apro i due file
        file = fopen("frase.txt", "r");
        verificata = fopen("frase_verificata.txt", "r");

        // salvo il contenuto su stringa_finale
        fgets(stringa, DIM, file);
        fgets(stringa_finale, DIM_FIN, verificata);

        // Apro e scrivo nel file 'report.txt'
        report = fopen("report.txt", "w");
        fputs(stringa, report);
        fputs(stringa_finale, report);

        // Chiudo i file
        fclose(file);
        fclose(verificata);
        fclose(report);
    }
    else // errore
    {
        perror("Errore generazione primo processo!\n");
        exit(1); // uscita con errore
    }

    return 0;
}