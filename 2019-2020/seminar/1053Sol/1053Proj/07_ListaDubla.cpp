#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodD {
	Student stud; // date de procesat
	NodD *next, *prev;	  // date/info de legatura/implementare relatie de ordine intre noduri
};

struct ListaDubla {
	NodD *prim, *ultim;
};


ListaDubla insertNodeEndLD(ListaDubla lst, Student s) {
	NodD * nou = (NodD*)malloc(sizeof(NodD));
	nou->next = NULL;
	nou->prev = lst.ultim;
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare partajare temporara adresa heap pentru nume student
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	
	if (lst.prim == NULL)
		lst.prim = lst.ultim = nou;
	else {
		lst.ultim->next = nou; // actualizare legatura sfarsit lista dubla catre noul sfarsit de lista (nou)
		lst.ultim = nou; // actualizare pointer sfarsit de lista
	}

	return lst;
}


// parsare lista dubla
void printListD(ListaDubla lst) {
	NodD* temp = lst.prim;
	while (temp) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}
}


// interschimb de noduri adiacente prin modificarea adreselor de legatura (prin modificare campuri next si prev)
ListaDubla interschimbAdiacenteLD(ListaDubla lst, int poz) { // poz - pozitia nodului 1 din interschimb 
	NodD *p = NULL, *q = NULL, *r = NULL, *s = NULL;
	// cazuri particulare
	// 1. lista contine 0 sau 1 nod -> interschimb ne-efectuat
	if (lst.prim == NULL || lst.prim->next == NULL)
		return lst;
	// 2. poz == 1 (interschimba nodul 1 cu nodul 2 in lista) -> un nou inceput de lista simpla
	if (poz == 1) {
		q = lst.prim;
		r = q->next;
		s = r->next;

		// modificare adrese de legatura pe next
		q->next = s;
		r->next = q;

		// modificare adrese de legatura pe prev
		q->prev = r;
		r->prev = NULL;

		if (s != NULL) {
			// lista contine cel putin 3 noduri
			// se actualizeaza doar inceputul de lista
			s->prev = q;
			lst.prim = r;
		}
		else {
			// lista contine doar 2 noduri care se si interschimba
			lst.prim = r;
			lst.ultim = q;
		}
	}
	else {
		// 3. poz == n (n - nr de noduri in lista); nodul 1 din interschimb este ultimul din lista -> interschimb ne-efectuat
		// 4. poz > n (n - nr noduri in lista)
		// caz general; pozitionare pe poz -> interschimb nod de pe poz cu nod de pe poz+1
		p = lst.prim;
		int i = 1;

		while (p && i< poz - 1) { // (poz - 1) este pozitia lui p in lista simpla
			p = p->next;
			i += 1;
		}

		if (p) { // daca FALSE -> caz particular nr. 4
				 // exista nod pe (poz-1) -> p
			if (p->next) { // daca FALSE -> caz particular nr. 4
						   // exista nod pe pozitia poz -> q
				q = p->next;
				if (q->next) { // daca FALSE -> caz particular nr. 3
							   // exista nod pe pozitia (poz + 1) -> r
					r = q->next;
					s = r->next;

					// p, q, r si s sunt fixate
					// modificare adrese de legatura pe next (comune)
					p->next = r;
					r->next = q;
					q->next = s;

					// modificare adrese de legatura pe prev (comune)
					q->prev = r;
					r->prev = p;

					if (s != NULL) {
						// r nu este ultimul nod -> cazul general de interschimb
						s->prev = q;
					}
					else {
						// r este ultimul nod din lista
						// se actualizeaza sfarsitul de lista
						lst.ultim = q;
					}
				}
			}
		}

	}

	return lst;
}

// interschimb noduri oarecare in LD
// sortare Bubble pe LD
// sortare selectie pe LD
// stergere nod din LD (oricare nod)

// implementare QuickSort (sir de valori stocat in vector, 
// utilizare stiva pentru gestionare capetelor de interval ce urmeaza a fi sortate in iteratiile urmatoare)

void main() {
	ListaDubla LD;
	LD.prim = LD.ultim = NULL;
	Student s;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {

		// incarcare date student in variabila s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		// inserare student in lista simpla (prim)
		LD = insertNodeEndLD(LD, s);

		s.nume = NULL; // evitare partajare zona de memorie aferenta numelui de student
	}

	printf("\nLista dupa creare:\n");
	printListD(LD);

	LD = interschimbAdiacenteLD(LD, 10);
	printf("\nLista dupa interschimb adiacente in lista dubla:\n");
	printListD(LD);

	fclose(f);
}