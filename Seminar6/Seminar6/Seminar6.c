﻿#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	long id;
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina) {
	printf("\n%ld. Masina %s are seria %d.",masina.id, masina.producator, masina.serie);
}

Masina initMasina(long id, const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.id = id;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void push(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

Masina pop(Nod** varf) { //extrag informatia utila si extrag nodul de la sfarsit
	//in cazul in care nu am date in lista
	Masina masina;
	masina.id = -1;
	masina.producator = NULL; //ca e pointer
	masina.serie = -1;
	//facem doar o singura iteratie
	if (*varf)
	{
		masina = (*varf)->inf; //dezalocarea pt informatia utila nu se face n functia pop ptc pierdem producatorul
		Nod* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp); //nu dezalocam inf utila
	}

	return masina;
}

Masina get(Nod** varf) { //extrag informatia utila si extrag nodul de la sfarsit
	//in cazul in care nu am date in lista
	Masina masina;
	masina.id = -1;
	masina.producator = NULL; //ca e pointer
	masina.serie = -1;
	//facem doar o singura iteratie
	if (*varf)
	{
		masina = (*varf)->inf; //dezalocarea pt informatia utila nu se face n functia pop ptc pierdem producatorul
		Nod* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp); //nu dezalocam inf utila
	}

	return masina;
}

void put(Nod** cap, Masina masina) {
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


Masina cautareDupaId(Nod** stiva, long id) {
	Masina masina;
	masina.id = -1;
	masina.producator = NULL; 
	masina.serie = -1;
	Nod* stivaAuxiliara = NULL;
	while ((*stiva)!=NULL && (*stiva)->inf.id != id)
	{
		push(&stivaAuxiliara,pop(stiva));
	}
	if (*stiva)
	{
		masina = pop(stiva); //scoatem masina cu id 3
	}
	while (stivaAuxiliara)
	{
		push(stiva, pop(&stivaAuxiliara));
	}

	return masina;
}

void main() {
	Nod* stiva = NULL;	
	//stiva
	Masina masina;
	push(&stiva, initMasina(1,"Renault", 1234));
	push(&stiva, initMasina(2,"Ford", 5678));
	push(&stiva, initMasina(3,"Ford", 5679));
	push(&stiva, initMasina(4,"Ford", 5677));
	push(&stiva, initMasina(5,"Peugeot", 9101));
	push(&stiva, initMasina(6,"Bmw", 1213));
	Masina masinaCautata = cautareDupaId(&stiva, 3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);
	printf("\n Stiva: ");
	while (stiva)
	{
		masina = pop(&stiva);
		afisareMasina(masina);
		free(masina.producator);
	}

	

	//coada

	Nod* coada = NULL;
	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Ford", 5677));
	put(&coada, initMasina(5, "Peugeot", 9101));
	put(&coada, initMasina(6, "Bmw", 1213));
	printf("\n Coada: ");
	while (coada)
	{
		masina = get(&coada);
		afisareMasina(masina);
		free(masina.producator);
	}
	
}