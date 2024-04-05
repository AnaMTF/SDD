#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina info;
	Nod* next;
};

void afisareMasina(Masina masina) {
		printf("Masina %s are seria %d\n", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {

	Masina masinaNoua;
	masinaNoua.producator = (char*)malloc(sizeof(char)*(strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);
	masinaNoua.serie = serie;
	return masinaNoua;
}

void inserareLaInceput(Nod** cap, Masina masina) {
	//pas 1 alocam mem nod nou
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	//pas 2 initializam nodul nou
	nodNou->info = masina; //shallow copy util ptc facem doar o dezalocare
	nodNou->next = *cap;
	//pas 3 modificam adresa de inceput
	*cap = nodNou;
}

void inserareLaSfarsit(Nod** cap, Masina masina) {
	//pas 1 alocam mem nod nou
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	//pas 2 initializam nodul nou
	nodNou->info = masina; //shallow copy util ptc facem doar o dezalocare
	nodNou->next = NULL;
	//parcurg lista pana la ultimul nod si fac legatura dintre ultimul nod si nodul nou
	if (*cap != NULL) {
		Nod* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	else
	{
		*cap = nodNou;
	}
}

//inserare dupa pozitie
void inserareDupaPozitie(Nod** cap, Masina masina, int pozitie) {
	if (pozitie == 0 || *cap == NULL) {
		inserareLaInceput(cap, masina);
	}
	else {
		Nod* temp = *cap;
		int contor = 0;
		while (temp && contor < pozitie - 1) {
			temp = temp->next;
			contor++;
		}
		if (temp) {
			Nod* nodNou = (Nod*)malloc(sizeof(Nod));
			nodNou->info = masina;
			nodNou->next = temp->next;
			temp->next = nodNou;
		}
		else {
			printf("Pozitie invalida\n");
		}
	}
}

//inserare dupa element dat
void inserareDupaProducator(Nod** cap, Masina masina, const char* producator) {
	Nod* temp = *cap;
	while (temp != NULL) {
		if (strcmp(temp->info.producator, producator) == 0) {
			Nod* nodNou = (Nod*)malloc(sizeof(Nod));
			if (nodNou == NULL) {
				printf("Eroare la alocare de memorie!\n");
				return;
			}
			nodNou->info = masina;
			nodNou->next = temp->next;
			temp->next = nodNou;
			return; // În acest punct inserarea a fost efectuată, deci putem ieși din funcție
		}
		temp = temp->next;
	}
	// Dacă nu am găsit producătorul în listă, putem adăuga masina la sfârșit
	inserareLaSfarsit(cap, masina);
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while (*cap)
	{
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.producator);
		free(temp);
	}
}

int cautareMasina(Nod* cap, const char* producator) {
	int numar = 0;
	while (cap) {
		if (strcmp(cap->info.producator, producator) == 0) {
			numar++;
		}
		cap = cap->next;
	}
	return numar;
}

void main() {
	//definim lista goala
	Nod* cap = NULL;

	//inserare la inceput de masini
	inserareLaInceput(&cap, initMasina("Dacia", 123)); //asta ajunge ultimul nod
	inserareLaInceput(&cap, initMasina("BMW", 124));
	inserareLaInceput(&cap, initMasina("Audi", 125));
	inserareLaInceput(&cap, initMasina("Audi", 120));
	inserareLaInceput(&cap, initMasina("Audi", 127));
	inserareLaInceput(&cap, initMasina("Ford", 126)); //asta ajunge primul nod

	//traversare lista
	traversareLista(cap);

	//inserare la sfarsit
	inserareLaSfarsit(&cap, initMasina("Skoda", 127));

	//traversare lista
	printf("\n\nDupa inserare la sfarsit \n");
	traversareLista(cap);

	//cautare in lista
	int numarAparitiiAudi = cautareMasina(cap, "Audi");
	printf("\n\nAudi apare de %d ori in lista\n", numarAparitiiAudi);

	//inserare dupa pozitie
	inserareDupaPozitie(&cap, initMasina("Mercedes", 128), 2);
	printf("\n\nDupa inserare dupa pozitie \n");
	traversareLista(cap);

	//inserare dupa producator
	inserareDupaProducator(&cap, initMasina("Mercedes2", 129), "Audi");
	printf("\n\nDupa inserare dupa producator \n");
	traversareLista(cap);

	//dezalocare lista
	dezalocare(&cap); //nu mai trebuie sa punem NULL la cap

	
}
