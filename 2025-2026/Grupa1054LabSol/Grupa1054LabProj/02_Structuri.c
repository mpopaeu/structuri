

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
	struct Angajat ang;

	return 0;
}