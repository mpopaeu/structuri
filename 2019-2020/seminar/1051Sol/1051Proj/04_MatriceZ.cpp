#include <stdio.h>
#include <malloc.h>
#include <string.h>

void main() {
	// matrice zig-zag de string-uri preluate din fisier text
	char ** pStrings; // matrice cu elemente de tip char; vector cu elemente de tip vector de char
	int nr = 0; // numarul de string-uri identificate in fisier

	FILE * f; // pointer la structura FILE
	char buffer[100]; // vector cu rol de stocare temporara a continutului preluat din fisier

	f = fopen("strings.txt", "r");
	while (fgets(buffer, sizeof(buffer), f)) { // fgets - citire linie din fisierul text f
		nr += 1; // incrementez numarul curent de linii (string-uri)
	}

	pStrings = (char **)malloc(nr * sizeof(char*)); // alocare vector de adrese de linii

	fseek(f, 0, SEEK_SET); // plasare cursor operatii r/w in fisierul f
	memset(buffer, 0, sizeof(buffer));
	int i = 0;
	while (fgets(buffer, sizeof(buffer), f)) { // fgets - citire linie din fisierul text f
		pStrings[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(pStrings[i], buffer);
		i += 1;
	}

	// afisare matrice zig-zag (vector de string-uri)
	for (i = 0; i < nr; i++)
		printf("%s", pStrings[i]); // afisare string de pe linia i


	// dezalocare matrice
	for (i = 0; i < nr; i++)
		free(pStrings[i]); // dezalocare linie i
	free(pStrings); // dezalocare vector de pointeri la linii


	fclose(f);

}