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
	Student stud;
	Nod* next;
};

Nod* inserareNodSfarsit(Nod* lista, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->stud = s; // copiere byte cu byte a lui s peste nou->st; partajare temporara nume student ca si locatie de heap
	nou->next = NULL; // nou devine ultimul nod in lista simpla

	if (lista == NULL) // nu exista nici un nod in lista
		return nou;
	else {
		// lista are cel putin 1 nod
		Nod* temp = lista;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // actualizare legatura sfarsit de lista catre nodul care se insereaza
	}

	return lista;
}

// interschimb noduri adiacente cu modificarea adreselor de legatura
// 1. lista contine 0 sau 1 nod -> nu exista interschimb
// 2. primul nod al interschimbului este ultimul nod / nu exista in lista -> interschimbul nu se realizeaza
// 3. primul nod al interschimbului este primul nod din lista -> modificare adresei de inceput al listei

Nod* interschimbNoduriAdiacente(Nod* lst, int idStud)
{
	// caz part 1
	if (lst == NULL || lst->next == NULL)  return lst;

	Nod *p = NULL, *q = NULL, *r = NULL, *s = NULL;
	// caz part 3
	if (lst->stud.id == idStud) {
		q = lst;
		r = q->next;
		s = r->next;

		q->next = s;
		r->next = q;

		return r;
	}

	// caz part 2
	// caz general
	p = lst;

	// traversare lista simpla cu vericare id student
	// p este nodul predecesor lui q, deci se testeaza id student din p->next
	while (p->next)
	{
		q = p->next;
		if (q->stud.id == idStud) {
			// studentul a fost identificat in lista
			if (q->next != NULL) { // q->next == NULL inseamna q ultimul nod; se termina de traversat lista si se inchide while
				// cazul general
				r = q->next;
				s = r->next;

				p->next = r;
				q->next = s;
				r->next = q;

				return lst;
			}
		}

		p = p->next;
	}

	return lst; // caz part 2: q este ultimul nod sau q nu exista in lista simpla
}

Nod* sortareBubble(Nod* lst) {
	char flag = 1; // semnaleaza reluarea comparatiilor pe lista simpla

	while (flag == 1) {
		Nod *temp_curent = lst;
		flag = 0; // lista sortata

		while (temp_curent->next != NULL) {
			Nod *temp_succ = temp_curent->next;
			if (temp_curent->stud.id > temp_succ->stud.id) {
				// nu se respecta criteriul de sortare pt temp_curent si temp_succesor
				// are loc interschimb intre cele 2 noduri
				// marchez cu flag interschimbul
				flag = 1; // lista nu este sortata
				lst = interschimbNoduriAdiacente(lst, temp_curent->stud.id);
			}

			temp_curent = temp_curent->next;
		}
	}

	return lst;
}

// interschimb noduri oarecare in lista simpla
// caz part 1: lista contine 0 sau 1 nod -> abandon interschimb
// caz part 2: cel putin unul din cele doua id studenti nu este regasit in lista -> abandon interschimb
// caz part 3: id studenti identice -> abandon interschimb
// caz part 4: unul din cele 2 id studenti este in primul nod din lista -> se modifica adresa de inceput a listei
// caz part 5: id studenti sunt in noduri succesive/adiacente -> interschimb de noduri adiacente (idStud1, idStud2) sau (idStud2, idStud1)
Nod* interschimbNoduriOarecare(Nod* lst, int idStud1, int idStud2)
{
	if (lst == NULL || lst->next == NULL) return lst; // caz part 1
	if (idStud1 == idStud2) return lst; // caz part 3

	Nod *p = NULL, *q = NULL, *r = NULL;
	Nod *s = NULL, *t = NULL, *v = NULL;
	// traversarea nr. 1 pt gasirea nodului q in lista
	if (lst->stud.id == idStud1) {
		// q este primul nod din lista
		q = lst;
		r = q->next;
	}
	else {
		// parsare lista simpla pt identificare lui idStud1
		p = lst;
		char gasit = 0;
		while (p->next && (gasit == 0)) {
			if (p->next->stud.id == idStud1) {
				// a fost identificat studentul q in lista
				q = p->next;
				r = q->next;
				gasit = 1;
			}

			p = p->next;
		}
	}

	// traversarea nr. 2 pt gasirea nodului t in lista
	if (lst->stud.id == idStud2) {
		// t este primul nod din lista
		t = lst;
		v = q->next;
	}
	else {
		// parsare lista simpla pt identificare lui idStud2
		s = lst;
		char gasit = 0;
		while (s->next && (gasit == 0)) {
			if (s->next->stud.id == idStud2) {
				// a fost identificat studentul t in lista
				t = s->next;
				v = t->next;
				gasit = 1;
			}

			s = s->next;
		}
	}

	if (q == NULL || t == NULL) return lst; // caz part 2: cel putin un nod nu a fost gasit in lista
	if (q->next == t)
		return interschimbNoduriAdiacente(lst, q->stud.id); // caz part 5: interschimb adiacente (q, t)
	if (t->next == q)
		return interschimbNoduriAdiacente(lst, t->stud.id); // caz part 5: interschimb adiacente (t, q)

	// caz part 4: unul din cele 2 noduri este inceput de lista
	if (q == lst) {
		// q este primul nod in lista
		t->next = r;
		s->next = q;
		q->next = v;

		return t; // noul inceput de lista
	}

	if (t == lst) {
		// t este primul nod in lista
		p->next = t;
		t->next = r;
		q->next = v;

		return q; // nou inceput de lista
	}

	// caz general
	p->next = t;
	t->next = r;
	s->next = q;
	q->next = v;

	return lst; // se returneaza acelasi inceput de lista (nu se modifica inceputul de lista)
}

// stergere nod pe baza de id student
Nod* stergereNod(Nod* lst, int idStud) {
	if (lst) {
		Nod* t = lst;
		if (lst->stud.id == idStud) { // se sterge primul nod
			lst = lst->next;
			free(t->stud.nume);
			free(t);
		}
		else {
			char gasit = 0;
			Nod* q = NULL;
			while (t->next && (gasit == 0)) {
				if (t->next->stud.id == idStud) {
					q = t->next;
					gasit = 1;
				}
			}
			if (q) {
				//  q este nodul care trebuie sters
				t->next = q->next;
				free(q->stud.nume);
				free(q);
			}
		}
	}
	return lst;
}
// dezalocare lista simpla
Nod* dezalocareLista(Nod* lst) {
	if (lst) {
		Nod *t = NULL;
		while (lst) {
			t = lst;
			lst = lst->next;
			free(t->stud.nume);
			free(t);
		}
	}
	return lst;
}

////////
// sortare prin selectie etc (interschimb noduri oarecare)

// interschimb noduri adiacente in lista dubla
// interschimb noduri oarecare in lista dubla
// sortare pe lista dubla
// creare lista dubla
// dezalocare lista dubla

void main() {
	Nod* prim = NULL;
	Student s;
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// preluare continut fisier studenti; se initializeaza temporarul s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);
		
		// apel functie de inserare nod in lista simpla
		prim = inserareNodSfarsit(prim, s);

		s.nume = NULL; // eliminare partajare zona hep pt ultimul student inserat
	}

	printf("Traversare lista simpla dupa creare:\n");
	Nod* temp = prim;
	while (temp != NULL) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}


	//prim = interschimbNoduriAdiacente(prim, 13);
	//printf("\nTraversare lista simpla dupa interschimb:\n");
	//temp = prim;
	//while (temp != NULL) {
	//	printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

	//	temp = temp->next;
	//}


	prim = interschimbNoduriOarecare(prim, 51, 57);
	printf("\nTraversare lista simpla dupa interschimb oarecare:\n");
	temp = prim;
	while (temp != NULL) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}

	//prim = sortareBubble(prim);
	//printf("\nTraversare lista simpla dupa sortare Bubble:\n");
	//temp = prim;
	//while (temp != NULL) {
	//	printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

	//	temp = temp->next;
	//}

	fclose(f);
}