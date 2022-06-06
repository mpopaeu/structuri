#include <stdio.h>

struct Car {
	unsigned far : 1;
	unsigned inchis : 1;
	int kmBord;
	unsigned trMetru : 4;
	unsigned : 4;
	unsigned AC : 1;
	unsigned : 0;
	unsigned flag : 1;
};

typedef struct Car Car;

void main(int argc, char* argv[]) {

	Car myCar;

	char* pCar = (char*)&myCar; // mapare pointer peste locatia myCar

	for (int i = 0; i < sizeof(Car); i++) { // rescrierea zonei de memorie alocate variabilei myCar 
											// cu valori nule (nu este posibil din myCar deoarece 
											// exista campuri fara denumire care nu pot fi accesate din myCar)
		pCar[i] = 0x00; 
	}

	myCar.far = 2;
	myCar.inchis = 1;
	myCar.trMetru = 10;
	myCar.flag = 1;
	myCar.AC = 1;

	int* adr_biti = &myCar.kmBord;	// adresa camp de tip standard (nu este definit pe biti, 
									// deci campul este adresabil)
	*adr_biti = 34000;

	printf("Size Car = %d\n", sizeof(Car));
	printf("\nStare far: %d, Maxim turatii/minut: %d\n", myCar.far, myCar.trMetru);
	printf("\nKm bord: %d\n", myCar.kmBord);

	// unsigned* uadr_biti;
	// uadr_biti = &myCar.inchis;	// adresa camp definit pe biti nu poate fi obtinuta 
									// si utilizata (bitii nu sunt adresabili) -> eroare de compilare
}