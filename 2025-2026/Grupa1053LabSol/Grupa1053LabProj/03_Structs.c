#include <stdio.h>

struct Client
{
	char* nume;			// 4 bytes
	unsigned int id;	// 4 bytes
	unsigned char tip;	// 1 bytes
	unsigned int puncte;// 4 bytes
	float medie_cos;	// 4 bytes
};

typedef struct Client Client;

int main()
{

	printf("Dimesiune structura Client  = %d bytes\n", sizeof(Client));

	Client cl;

	cl.nume = "Popescu Georgia";
	cl.id = 18976;
	cl.tip = 'F'; // F pers fizica, J firma, O ONG, I institutie pub
	cl.puncte = 100;
	cl.medie_cos = (float)378.09;

	Client* pcl = &cl;

	printf("Nume client = %s\n", pcl->nume);
	printf("Valoarea cos mediu client = %f\n", (*pcl).medie_cos);


	return 0;
}