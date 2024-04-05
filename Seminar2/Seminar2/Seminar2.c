#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct Produs {
	float pret;
	int cod;
	char* denumire;
};
void citireVector(const char* numeFisier, int** vector, int* dimensiune) {
	//dereferentiere
	FILE* streamFisier = NULL; 
	streamFisier = fopen(numeFisier, "r");
	if (streamFisier != NULL)
	{
		fscanf(streamFisier, "%d", dimensiune); //e deja adresa. singurul caz in care nu avem nevoie de dereferentiere
		*vector = (int*)malloc(sizeof(int) * (*dimensiune));

		for(int i = 0; i< *dimensiune; i++)
		{
			fscanf(streamFisier, "%d", (*vector)+i); //&(*vector)[i] sau (*vector)+i
		}

		fclose(streamFisier);
	}
	
}

struct Produs preluareProdusDinFisier(FILE* file) {
	struct Produs produs;
	if (file != NULL)
	{
		char buffer[20]; //buffer de citire cu dimensiune din 3 parti
		fgets(buffer, 10, file); //7.5 \n aici ne folosim de atof
		produs.pret = atof(buffer);

		fgets(buffer, 10, file); //1\n
		produs.cod = atoi(buffer);

		fgets(buffer, 15, file); //Alune\n
		//strtok pt a taia \n
		char* denumire = strtok(buffer, "\n");
		produs.denumire = malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(produs.denumire, denumire);
	}
	return produs;
}

struct Produs* preluareVectorProduseDinFisier(FILE* file, int* nrProduse){
	struct Produs* vectorProduse = NULL;
	char buffer[20];
	if (file != NULL)
	{
		fgets(buffer, 20, file);
		*nrProduse = atoi(buffer);
		vectorProduse = malloc(sizeof(struct Produs) * (*nrProduse));
		for(int i = 0; i< *nrProduse; i++){
		
			fgets(buffer, 20, file);
			vectorProduse[i].pret = atof(buffer);

			fgets(buffer, 20, file);
			vectorProduse[i].cod = atoi(buffer);

			fgets(buffer, 20, file);
			char* denumire = strtok(buffer, "\n");
			vectorProduse[i].denumire = malloc(sizeof(char)* (strlen(denumire) + 1));
			strcpy(vectorProduse[i].denumire, denumire);
		}
		
	}
	return vectorProduse;
}

void afisareProdus(struct Produs produs);

void afisareVectorProduse(struct Produs* vectorProduse, int nrProduse) {
	for (int i = 0; i < nrProduse; i++)
	{
		printf("\n Produsul %s are codul %d si pretul de %.2f lei", vectorProduse[i].denumire, vectorProduse[i].cod, vectorProduse[i].pret);
		free(vectorProduse[i].denumire);
	}
	free(vectorProduse);
}

void main() {
	int val1, val2;
	//la test avem de preluat datele de intrare
	FILE* streamFisier = NULL; //e poiner
	streamFisier = fopen("Fisier.txt", "r"); //numele fisierului si modul de deschidere r-read
	if (streamFisier != NULL) //verificam daca s a deschis fisierul corect
	{
		//2 posibilitati fscanf si fgets
		fscanf(streamFisier, "%d", &val1); // trebuie mereu adresa, nu valori
		fscanf(streamFisier, "%d", &val2);
	}
	else
	{
		printf("Fisierul nu s-a deschis corect");
	}
	fclose(streamFisier); //inchidem fisierul

	printf("\n Valoarea val1 = %d, valoarea val2 = %d", val1, val2);


	//citire vector
	int* vector;
	int dimensiune;

	citireVector("Vector.txt",&vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++)
	{
		printf("\n vector[%i] = %d", i, vector[i]);
	}

	free(vector); //unde avem alocare avem si dezalocare

	FILE* file = NULL;
	file = fopen("Produs.txt", "r");

	struct Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);

	fclose(file);

	//citire vector de produse
	file = NULL;
	file = fopen("VectorProduse.txt", "r");

	int dimensiuneVP;
	struct Produs* vectorProduse = preluareVectorProduseDinFisier(file, &dimensiuneVP);

	afisareVectorProduse(vectorProduse, dimensiuneVP);

	fclose(file);

}

void afisareProdus(struct Produs produs) {
	printf("\n Produsul %s are codul %d si pretul de %.2f lei", produs.denumire, produs.cod, produs.pret);
}