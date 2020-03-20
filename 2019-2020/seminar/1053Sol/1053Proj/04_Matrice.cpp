#include <stdio.h>
#include <malloc.h>
#include <string.h>


void main() {

	// matrice in heap de string-uri (matrice zig-zag)
	// creare, afisare, dezalocare

	int n = 0; // calculez numarul de string-uri
	char ** pStrings; // pointer gestionare matrice zig-zag (lungimi diferite la nivel de linii)
	char buffer[100]; // buffer continut temporar preluat din fisier text

	FILE* f; // f - variabila locala pointer la structura FILE

	f = fopen("strings.txt", "r");

	while (fgets(buffer, sizeof(buffer), f)) { // a fost identificata o noua linie in fisierul text 
		n += 1; // incrementare numar de string-uri
	}

	pStrings = (char**)malloc(n * sizeof(char*)); // alocare vector intermediar de pointeri (adrese inceput linii)
	
	fseek(f, 0, SEEK_SET); // plasez cursor R/W din/in fisier la inceputul fisierului
	int i = 0; // i - linia curenta din matrice
	while (fgets(buffer, sizeof(buffer), f)) {
		pStrings[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char)); // + 1 pentru terminator de string
		strcpy(pStrings[i], buffer); // copiez string preluat din fisier in zona alocata (seg heap) mai sus
		i += 1;
	}

	// afisare continut matrice
	for (i = 0; i < n; i++)
		printf("%s", pStrings[i]);
	// printf("\n");


	// dezalocare matrice
	for (i = 0; i < n; i++)
		free(pStrings[i]);
	free(pStrings);

	fclose(f);
}