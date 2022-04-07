#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

// inserare nod in LS (inceput/sfarsit/interior)
// stergere nod din LS (inceput/sfarsit/interior)

// dezalocare LS
// export angajati in vector (LS devine empty)

void main()
{

}