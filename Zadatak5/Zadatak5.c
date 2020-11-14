#include<stdio.h>
#include<stdlib.h>

struct broj;
typedef struct broj* Pozicija;

typedef struct broj {
	int br;
	Pozicija next;
}_broj;

void ucitaj(char[20], Pozicija);
void unesiSortirano(Pozicija, int);
void unija(Pozicija, Pozicija, Pozicija);
void presjek(Pozicija, Pozicija, Pozicija);
void ispisi(Pozicija, char[20]);

int main() {
	_broj head;
	head.next = NULL;
	_broj first;
	first.next = NULL;
	_broj headUnija;
	headUnija.next = NULL;
	_broj headPresjek;
	headPresjek.next = NULL;

	ucitaj("Lista1.txt", &head);
	ucitaj("Lista2.txt", &first);
	unija(&head, &first, &headUnija);
	ispisi(&headUnija, "UNIJA:");
	presjek(&head, &first, &headPresjek);
	ispisi(&headPresjek, "PRESJEK:");

}

void ucitaj(char dat[20], Pozicija p) {
	FILE* ulz = fopen(dat, "r");
	if (ulz == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}

	Pozicija q = NULL;
	
	int pom = 0;
	while (!feof(ulz)) {
		fscanf(ulz, "%d", &pom);
		unesiSortirano(p, pom);
	}
}

void unesiSortirano(Pozicija p,int broj) {

	while (p->next != NULL && p->next->br < broj)
		p = p->next;

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Pozicija));
	q->br = broj;

	q->next = p->next;
	p->next = q;
}

void unija(Pozicija p, Pozicija q, Pozicija r) {
	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL) {
		if (p->br < q->br) {
			unesiSortirano(r, p->br);
			r = r->next;
			p = p->next;
		}
		else if (p->br > q->br) {
			unesiSortirano(r, q->br);
			r = r->next;
			q = q->next;
		}
		else {
			unesiSortirano(r, p->br);
			r = r->next;
			p = p->next;
			q = q->next;
		}
	}

	if (p == NULL)
		while (q != NULL) {
			unesiSortirano(r, q->br);
			q = q->next;
		}
	else
		while (p != NULL) {
			unesiSortirano(r, p->br);
			p = p->next;
		}
}

void presjek(Pozicija p, Pozicija q, Pozicija r) {
	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL) {
		if (p->br > q->br)
			q = q->next;

		else if (p->br < q->br)
			p = p->next;

		else {
			unesiSortirano(r, p->br);
			p = p->next;
			q = q->next;
			r = r->next;
		}
	}
}

void ispisi(Pozicija p, char pom[20]) {
	
	printf("\n");
	printf(pom);
	p = p->next;

	while (p != NULL) {
		printf("%d ", p->br);
		p = p->next;
	}
}