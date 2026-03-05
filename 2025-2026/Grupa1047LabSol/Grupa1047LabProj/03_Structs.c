#include <stdio.h>
#include <string.h>


struct Client
{
	unsigned int id;
	char* denumire;
	unsigned char tip;
	char ultima_comanda[11]; // 10 + 1; +1 pentru spatiu necesar terminatorului de string (byte 0x00)
	float valoare_totala_comenzi;
};

typedef struct Client Client;

int main()
{
	Client c;

	printf("Dimensiune Client = %d bytes\n", sizeof(Client));

	c.denumire = "Cosmin Popescu";
	c.id = 7654;
	c.tip = 'F';
	//c.ultima_comanda = "12/12/2025";
	strcpy(c.ultima_comanda, "12/12/2025");
	c.valoare_totala_comenzi = (float)10011.98;

	printf("Data ultima comanda (client c): %s\n", c.ultima_comanda);

	Client* pc = &c;
	
	printf("Data ultima comanda (pointer pc): %s\n", pc->ultima_comanda);

	return 0;
}