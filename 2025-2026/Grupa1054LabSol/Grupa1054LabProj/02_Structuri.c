#include <stdio.h>
#include <string.h>

struct Angajat {
	char* nume;
	char id[5]; // 1 byte rezervat pentru terminatorul de string
	unsigned char varsta;
	float salariu;
	char* functie;
};

typedef struct Angajat Angajat;

int main()
{
	Angajat ang;

	printf("Dimensiune structura Angajat = %d\n", sizeof(Angajat));

	ang.nume = "Popescu George";
	// ang.id = "ID01"; // adresa de stack seg a lui ang.id nu poate fi modificata
	strcpy(ang.id, "ID01");
	ang.varsta = 26;
	ang.salariu = 5500.5;
	ang.functie = "Analist";

	printf("ID angajat este (ang): %s\n", ang.id);

	Angajat* pang = &ang;

	printf("ID angajat este (pang): %s\n", pang->id);

	return 0;
}