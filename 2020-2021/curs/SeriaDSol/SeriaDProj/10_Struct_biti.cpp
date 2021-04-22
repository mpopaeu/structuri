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

#define CAR_FAR_MASK 0x01


int main(int argc, char* argv[]) {

	Car myCar;

	unsigned char* pCar = (unsigned char*)&myCar;

	for (int i = 0; i < sizeof(Car); i++) {
		pCar[i] = 0x00;
	}

	myCar.far = 1;
	myCar.inchis = 1;
	myCar.trMetru = 10;
	myCar.flag = 1;
	myCar.AC = 1;

	printf("Size Car = %d\n", sizeof(Car));
	printf("\nStare far: %d, Maxim turatii/minut: %d\n", myCar.far, myCar.trMetru);

	if (myCar.far == 1)
		printf("\n Stare far din myCar: %d\n", myCar.far);

	if((pCar[0] & CAR_FAR_MASK) == CAR_FAR_MASK)
		printf("\n Stare far utilizare masca CAR_FAR_MASK: %d\n", CAR_FAR_MASK);
	else
		printf("\n Stare far utilizare masca CAR_FAR_MASK: %d\n", (pCar[0] & CAR_FAR_MASK));

	// 0x03 = [00000011]
	// 0x01 = [00000001]
	// -----------------&
	// 0x01 = [00000001]


	return 0;
}