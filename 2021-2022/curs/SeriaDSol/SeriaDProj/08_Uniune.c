#include <string.h>
#include <stdio.h>

union Persoana {
	char CNP[13];
	int id;
	float check;
};

typedef union Persoana Persoana;

void main(int argc, char* argv[]) {

	Persoana pers;

	printf("Dimensiune Persoana = %d\n", sizeof(pers));

	printf("\nAdresa(pers.CNP)= %p, Cont(pers.CNP)= %s\n", &pers.CNP, pers.CNP);
	printf("\nAdresa(pers.id)= %p, Cont(pers.id)= %d\n", &pers.id, pers.id);
	printf("\nAdresa(pers.check)= %p, Cont(pers.check)= %f\n", &pers.check, pers.check);

	char* pPers = (char*)&pers;

	for (int i = 0; i < sizeof(pers); i++) {
		pPers[i] = 0x00;
	}

	printf("\nAdresa(pers.CNP)= %p, Cont(pers.CNP)= %s\n", &pers.CNP, pers.CNP);
	printf("\nAdresa(pers.id)= %p, Cont(pers.id)= %d\n", &pers.id, pers.id);
	printf("\nAdresa(pers.check)= %p, Cont(pers.check)= %f\n", &pers.check, pers.check);

	pers.id = 0x2871;

	printf("\nAdresa(pers.CNP)= %p, Cont(pers.CNP)= %s\n", &pers.CNP, pers.CNP);
	printf("\nAdresa(pers.id)= %p, Cont(pers.id)= %d\n", &pers.id, pers.id);
	printf("\nAdresa(pers.check)= %p, Cont(pers.check)= %f\n", &pers.check, pers.check);

	strcpy(pers.CNP, "1881111270981");
	printf("\nAdresa(pers.CNP)= %p, Cont(pers.CNP)= %s\n", &pers.CNP, pers.CNP);
	printf("\nAdresa(pers.id)= %p, Cont(pers.id)= %d\n", &pers.id, pers.id);
	printf("\nAdresa(pers.check)= %p, Cont(pers.check)= %f\n", &pers.check, pers.check);

	pers.check = (float)2411.36;
	printf("\nAdresa(pers.CNP)= %p, Cont(pers.CNP)= %s\n", &pers.CNP, pers.CNP);
	printf("\nAdresa(pers.id)= %p, Cont(pers.id)= %d\n", &pers.id, pers.id);
	printf("\nAdresa(pers.check)= %p, Cont(pers.check)= %f\n", &pers.check, pers.check);
}