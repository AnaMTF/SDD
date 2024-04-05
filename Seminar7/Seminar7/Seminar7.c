#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

struct HashTable {
	Nod** vector;  //vector alocat dinamic de pointeri la noduri
	int dim;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaFinal(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

HashTable initHashTable(int dim) {
	HashTable hashTable;
	hashTable.dim = dim;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hashTable.vector[i] = NULL;
	}
	return hashTable;
}

int fucntieHash(int serie, int dim) {
	return serie % dim;
}

void inserareInHT(HashTable ht, Masina masina) {

	if (ht.dim > 0) { //avem cel putin un element in vector
		int pozitie = fucntieHash(masina.serie, ht.dim);
		if (pozitie >= 0 && pozitie < ht.dim) {
			inserareLaFinal(&(ht.vector[pozitie]), masina);
		}
	}
}

void traversareHT(HashTable hashT) {
	for (int i = 0; i < hashT.dim; i++) {
		printf("\n pozitie: %d:", i);
		Nod* copie = hashT.vector[i];
		while (copie) {
			afisareMasina(copie->inf);  //dezalocare de &copie->inf
			copie = copie->next; //ma deplasez in lista de pe pozitia i a vectorului
		}
	}
}

//tema dezalocarea tabelei de dispersie
//void dezalocareLista(Nod** cap) {
//	while (*cap) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->inf.producator);
//		free(temp);
//	}
//}
//
//void dezalocareHT(HashTable hashT) {
//	for (int i = 0; i < hashT.dim; i++) {
//		dezalocareLista(&(hashT.vector[i]));
//	}
//	free(hashT.vector);
//}

void main() {
	int dimensiune = 10;
	HashTable hashT = initHashTable(dimensiune);

	inserareInHT(hashT, initMasina("Renault", 1234));
	// e ok sa transmit hasT prin valoare deoarece adresele sunt deja initializate la initHaashTable
	inserareInHT(hashT, initMasina("Ford", 5678));
	inserareInHT(hashT, initMasina("Ford", 5679));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Peugeot", 9101));
	inserareInHT(hashT, initMasina("Ford", 5677)); //cliziune pe pozitia 7
	inserareInHT(hashT, initMasina("Bmw", 1213));

	traversareHT(hashT);
	traversareHT(hashT);

	//tema dezalocarea tabelei de dispersie
	//dezalocareHT(hashT);
	traversareHT(hashT);
}