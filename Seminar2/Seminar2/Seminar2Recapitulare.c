#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int cod;
	float pret;
	char* denumire;
} Produs;

void citireFisier(char* numeFisier, int* val1, int* val2) {
	FILE* fisier = NULL;
	printf("Val1 inainte de citire = %d Adresa lui Val1 = %X, \n", *val1, val1);
	printf("Val2 inainte de citire = %d Adresa lui Val2 = %X \n", *val2, val2);

	//citire 2 valori din fisier

	fisier = fopen(numeFisier, "r");
	if (fisier != NULL) {

		fscanf(fisier, "%d", val1);
		fscanf(fisier, "%d", val2);

	}
	else {
		printf("Fisierul nu a putut fi deschis");
	}

	fclose(fisier);
	fisier = NULL;
}

void citireVector2(char* numeFisier, int** vectorFisier, int* dimensiune) {
	FILE* fisier = NULL;
	printf("Dimensiunea inainte de citire = %d Adresa lui Dimensiune = %X, \n", *dimensiune, dimensiune);
	fisier = fopen(numeFisier, "r");
	if (fisier != NULL) {
		fscanf(fisier, "%d", dimensiune);
		*vectorFisier = (int*)malloc(sizeof(int) * (*dimensiune));
		for (int i = 0; i < *dimensiune; i++) {
			fscanf(fisier, "%d", &(*vectorFisier)[i]);
			printf("Vector[%d] din functie = %d \n", i, (*vectorFisier)[i]);
		}
	}
	else {
		printf("Fisierul nu a putut fi deschis");
	}
	fclose(fisier);
	fisier = NULL;
}

Produs citireProdusFisier(char* numeFisier) {
	Produs produs;
	FILE* fisier = NULL;
	fisier = fopen(numeFisier, "r");

	if (fisier !=NULL)
	{
		char buffer[30];
		fgets(buffer, 30, fisier);
		produs.pret = atof(buffer);

		fgets(buffer, 30, fisier);
		produs.cod = atoi(buffer);

		fgets(buffer, 30, fisier);
		char* denumire = strtok(buffer, "\n");
		produs.denumire = malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(produs.denumire, denumire);
	}
	else
	{
		printf("Fisierul nu a putut fi deschis");
	}

	fclose(fisier);
	fisier = NULL;
	return produs;
}

Produs* citireVectorProduseFisier(char* numeFisier, int* nrProduse) {
	FILE* fisier = NULL;
	Produs* vectorProduse = NULL;
	fisier = fopen(numeFisier, "r");
	char* buffer[30];

	if (fisier != NULL)
	{
		fgets(buffer, 30, fisier);
		*nrProduse = atoi(buffer);
		vectorProduse = (Produs*)malloc(sizeof(Produs) * (*nrProduse));

		for (int i = 0; i < *nrProduse; i++)
		{
			fgets(buffer, 30, fisier);
			vectorProduse[i].pret = atof(buffer);

			fgets(buffer, 30, fisier);
			vectorProduse[i].cod = atoi(buffer);

			fgets(buffer, 30, fisier);
			char* denumire = strtok(buffer, "\n");
			vectorProduse[i].denumire = malloc(sizeof(char) * (strlen(denumire) + 1));
			strcpy(vectorProduse[i].denumire, denumire);
		}
	}
	else
	{
		printf("Fisierul nu a putut fi deschis");
	}

	fclose(fisier);
	return vectorProduse;
}

void main1() {
	int val1 = 0, val2 = 0;
	char numeFisier[30] = "fisier.txt";

	citireFisier(numeFisier, &val1, &val2);
	printf("Val1 dupa citire = %d Adresa lui Val1 = %X, \n", val1, &val1);
	printf("Val2 dupa citire = %d Adresa lui Val2 = %X \n", val2, &val2);

	strcpy(numeFisier, "Vector.txt");
	int* vectorFisier = NULL;
	int dimensiune = 0;
	citireVector2(numeFisier, &vectorFisier, &dimensiune);
	printf("Dimensiunea dupa citire = %d Adresa lui Dimensiune = %X, \n", dimensiune, &dimensiune);
	for (int i = 0; i < dimensiune; i++)
	{
		printf("Vector[%d] = %d \n", i, vectorFisier[i]);
	}
	free(vectorFisier);
	vectorFisier = NULL;
	strcpy(numeFisier, "Produs.txt");
	Produs produs = citireProdusFisier(numeFisier);
	
	
	printf("Produsul citit are codul %d, pretul %.2f si denumirea %s", produs.cod, produs.pret, produs.denumire);
	free(produs.denumire);
	produs.denumire = NULL;

	Produs* vectorProduse = NULL;
	strcpy(numeFisier, "VectorProduse.txt");
	dimensiune = 0;
	vectorProduse = citireVectorProduseFisier(numeFisier, &dimensiune);
	
	for (int i = 0; i < dimensiune; i++)
	{
		printf("Produsul %s are codul %d si pretul de %.2f lei \n", vectorProduse[i].denumire, vectorProduse[i].cod, vectorProduse[i].pret);
		free(vectorProduse[i].denumire);
	}

	free(vectorProduse);
	
	
	
	return 0;
}