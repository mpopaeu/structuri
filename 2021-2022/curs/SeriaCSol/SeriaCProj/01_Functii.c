#include <stdio.h>

int main(int argc, char* argv[]) {

	printf("\nNumarul de argumente al functiei main este: %d\n", argc);
	for (int i = 0; i < argc; i++)
		printf("\nArgumentul %d este: %s\n", i + 1, argv[i]);

	// Utilizare argumente pentru determinare suma 
	int* pArgs;
	// Alocare spatiu vector de valori (primul argument este numele fisierului exe)
	pArgs = (int*)malloc((argc - 1) * sizeof(int));

	// conversie argumente functie main din char* in int (ASCII-to-binary)
	for (int i = 0; i < argc - 1; i++)
		pArgs[i] = atoi(argv[i + 1]);

	int suma = 0;
	for (int i = 0; i < argc - 1; i++)
		suma += pArgs[i];

	printf("\nSuma este: %d\n", suma);

	free(pArgs);
	return 0;
}