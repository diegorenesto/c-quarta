// Leggere il file testo.txt e mostrane il contenuto a video.

#include <stdio.h>

int main(int argc, char *argv[])
{

	FILE *fd;
	char contenuto[100];

	// apro file
	fd = fopen("testo.txt", "r");

	fgets(contenuto, sizeof(contenuto), fd); // dove salvo, quanto leggo, da dove leggo

	// chiudo il file
	fclose(fd);
	printf("Il contenuto del file è: %s\n", contenuto);

    return 0;
}