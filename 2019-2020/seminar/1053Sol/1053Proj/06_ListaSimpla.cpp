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

struct Nod {
	Student stud; // date de procesat
	Nod* next;	  // date/info de legatura/implementare relatie de ordine intre noduri
};

Nod* insertNodeEnd(Nod* lst, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->stud = s; // asumata partajarea lui nume
	nou->next = NULL;
	if (lst == NULL) // lista este goala/empty
		return nou; 
	else {
		// exista cel putin 1 nod in lista
		Nod* temp = lst;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // legare nodul nou la sfarsitul listei lst
	}

	return lst;
}

// parsare lista simpla
void printList(Nod* lst) {
	Nod* temp = lst;
	while (temp) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}
}

// stergere/dezalocare nod din lista simpla (la inceputul listei)

// dezalocare lista simpla

// interschimb de noduri adiacente prin modificarea adreselor de legatura (prin modificare campuri next)
Nod* interschimbAdiacente(Nod* lst, int poz) { // poz - pozitia nodului 1 din interschimb 
	Nod *p = NULL, *q = NULL, *r = NULL, *s = NULL;
	// cazuri particulare
	// 1. lista contine 0 sau 1 nod -> interschimb ne-efectuat
	if (lst == NULL || lst->next == NULL)
		return lst;
	// 2. poz == 1 (interschimba nodul 1 cu nodul 2 in lista) -> un nou inceput de lista simpla
	if (poz == 1) {
		q = lst;
		r = lst->next;
		s = r->next;

		// modificare adrese de legatura
		q->next = s;
		r->next = q;
		lst = r; // actualizare adresa de inceput lista simpla
	}
	else {
		// 3. poz == n (n - nr de noduri in lista); nodul 1 din interschimb este ultimul din lista -> interschimb ne-efectuat
		// 4. poz > n (n - nr noduri in lista)
		// caz general; pozitionare pe poz -> interschimb nod de pe poz cu nod de pe poz+1
		p = lst;
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
					// modificare adrese de legatura caz general
					p->next = r;
					r->next = q;
					q->next = s;
				}
			}
		}
		
	}

	return lst;
}

int nrNoduri(Nod* lst) {
	int n = 0;
	Nod * temp = lst;
	while (temp) {
		n += 1;
		temp = temp->next;
	}

	return n;
}

// interschimb noduri oarecare in lista simpla (poz1, poz2)
// cazuri particulare (lista simpla)
// 0.1 poz1 > poz2 -> intreschimb poz1 cu poz 2
// 0.2 poz1 == poz2 -> interschimbul nu are sens
// 1. lista contine 0 sau 1 nod -> interschimb ne-efectuat
// 2. poz1 == 1 (interschimba nodul 1 cu nodul poz2 in lista) -> un nou inceput de lista simpla
// 3. poz1 >= n (n - nr de noduri in lista); nodul 1 din interschimb este ultimul din lista/nu exista in lista -> interschimb ne-efectuat
// poz2 > n
// 4. poz2 == poz1 + 1 -> intreschimb de noduri adiacente
Nod* interschimbOarecare(Nod* lst, int poz1, int poz2) {
	if (lst == NULL || lst->next == NULL)
		return lst;
	if (poz1 == poz2)
		return lst;
	if (poz1 > poz2) {
		int aux = poz1;
		poz1 = poz2;
		poz2 = aux;
	}

	int n = nrNoduri(lst);
	if (poz1 >= n || poz2 > n)
		return lst;

	if (poz2 == poz1 + 1)
	{
		// caz particular 4
		lst = interschimbAdiacente(lst, poz1);
		return lst;
	}

	// cazul particular 2
	// cazul general
	// fixarea/stabilirea celor 6 pointeri pe nodurile implicate in interschimb
	Nod *p = NULL, *q = NULL, *r = NULL, *s = NULL, *t = NULL, *v = NULL;

	if (poz1 == 1) {
		// caz particular 2
		q = lst;
		r = q->next;
	}
	else {
		// caz general
		p = lst;
		int i = 1;
		while (i < poz1 - 1) {
			i += 1;
			p = p->next;
		} 
		q = p->next;
		r = q->next;
	}

	s = lst;
	int i = 1;
	while (i < poz2 - 1) {
		i += 1;
		s = s->next;
	}
	t = s->next;
	v = t->next;

	// implementare interschimb propriu-zis
	t->next = r;
	s->next = q;
	q->next = v;

	if (poz1 == 1) {
		lst = t;
	}
	else {
		p->next = t;
	}

	return lst;
}

// sortare lista simpla (bubble, selectie etc)
Nod* sortareBubble(Nod* lst) {
	char flag = 1; // 1 - reluare traversare lista in vederea validarii

	int i;

	while (flag == 1) {
		// trebuie sa reiau traversarea listei incepand cu primul nod
		Nod* temp = lst;
		i = 1;
		flag = 0;

		while (temp->next != NULL) {
			Nod *temp_next = temp->next;
			if (temp->stud.id > temp_next->stud.id) {
				// relatia de ordine este invalida
				lst = interschimbAdiacente(lst, i);
				flag = 1;
				// i += 1;
			}
			else {
				temp = temp->next;
				// i += 1;
			}
			i += 1;
		}
	}

	return lst;
}

void main() {
	Nod * prim = NULL; 
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
		prim = insertNodeEnd(prim, s);

		s.nume = NULL; // evitare partajare zona de memorie aferenta numelui de student
	}

	printf("\nLista dupa creare:\n");
	printList(prim);

	//prim = sortareBubble(prim);
	//printf("\nLista dupa sortare Bubble:\n");
	//printList(prim);

	// prim = interschimbAdiacente(prim, 5);
	prim = interschimbOarecare(prim, 2, 3);
	printf("\nLista dupa interschimb:\n");
	printList(prim);


	fclose(f);
}