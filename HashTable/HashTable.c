#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct Produs Produs;
typedef struct HashTable HashTable;

struct Produs {
	int id;
	char* denumire;
	float pret;
};

struct Nod {
	Produs info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int nrElemente;
};

void afisareProdus(Produs prod) {
	printf("\nID: %5d\nNUME: %20s\nPRET: %4.2f\n", prod.id, prod.denumire, prod.pret);
}

Produs initProdus(int id, char* nume, float pret) {
	Produs produsNou;
	produsNou.id = id;
	produsNou.denumire = (char*)malloc(strlen(nume) * sizeof(char) + 1);
	strcpy(produsNou.denumire, nume);
	produsNou.pret = pret;

	return produsNou;
}

Produs initProdusFisier(FILE* fisier) {
	Produs prod;
	if (fisier) {
		char* buffer[20];

		fgets(buffer, 20, fisier);
		prod.id = atoi(buffer);

		fgets(buffer, 20, fisier);
		char* denumire = strtok(buffer,"\n");
		prod.denumire = (char*)malloc(strlen(denumire) * sizeof(denumire) + 1);
		strcpy(prod.denumire, denumire);

		fgets(buffer, 20, fisier);
		prod.pret = atof(buffer);
	}
	return prod;
}

Produs initProdTastatura() {
	Produs prod;

	char* buffer[20];

	printf("\nID: ");
	scanf("%d", &prod.id);
	printf("\nDENUMIRE: ");
	scanf("%s", buffer);
	prod.denumire = (char*)malloc(strlen(buffer) * sizeof(char) + 1);
	strcpy(prod.denumire, buffer);
	printf("\nPRET: ");
	scanf("%f", &prod.pret);

	return prod;
}

void inserareLaFinal(Nod** cap, Produs prod) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = prod;
	nodNou->next = NULL;
	if (*cap) {
		Nod* nodCurent = *cap;
		while (nodCurent->next)
		{
			nodCurent = nodCurent->next;
		}
		nodCurent->next = nodNou;
	}
	else
	{
		*cap = nodNou;
	}
}

int functieHash(int id, int dim) {
	return id % dim;
}

HashTable initHashTable(int dim) {
	HashTable ht;
	ht.nrElemente = dim;
	ht.vector = (Nod**)malloc(dim * sizeof(Nod*));
	for (int i = 0; i < dim; i++)
	{
		ht.vector[i] = NULL;
	}
	return ht;
}

void inserareHT(HashTable ht, Produs prod) {
	if (ht.nrElemente>0)
	{
		int pozitie = functieHash(prod.id, ht.nrElemente);
		if (pozitie < ht.nrElemente) {
			inserareLaFinal(&(ht.vector[pozitie]), prod);
		}
	}
}

void traversareLS(Nod* cap) {
	while (cap)
	{
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

void traversareHT(HashTable ht) {
	if (ht.nrElemente > 0) {
		for (int i = 0; i < ht.nrElemente; i++)
		{
			if (ht.vector[i]) {
				printf("\n~~~~~~~~~~Pozitia: %d~~~~~~~~~\n", i);
				traversareLS(ht.vector[i]);
			}
		}
	}
}

void dezalocareLS(Nod** cap) {
	while (*cap)
	{
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie->info.denumire);
		free(copie);
	}
}

void dezalocareHT(HashTable ht) {
	for (int i = 0; i < ht.nrElemente; i++)
	{
		if (ht.vector[i]) {
			dezalocareLS(&(ht.vector[i]));
		}
	}
	free(ht.vector);
}

void main() {
	HashTable ht = initHashTable(10);

	inserareHT(ht, initProdus(1, "Masline", 44.1));
	inserareHT(ht, initProdus(2, "Apa", 4.4));
	inserareHT(ht, initProdus(3, "Pringles", 12.08));
	inserareHT(ht, initProdus(4, "Castraveti", 3.66));
	inserareHT(ht, initProdus(1, "Masline", 144.1));
	inserareHT(ht, initProdus(12, "Apa", 14.4));
	inserareHT(ht, initProdus(13, "Pringles", 112.08));
	inserareHT(ht, initProdus(14, "Castraveti", 13.66));

	FILE* fisier = fopen("produse.txt", "r");
	if (fisier)
	{
		while (!feof(fisier))
		{
			inserareHT(ht, initProdusFisier(fisier));
		}
	}
	

	//inserareHT(ht, initProdTastatura());
	//inserareHT(ht, initProdTastatura());
	//inserareHT(ht, initProdTastatura());

	traversareHT(ht);

	dezalocareHT(ht);
	fclose(fisier);
}