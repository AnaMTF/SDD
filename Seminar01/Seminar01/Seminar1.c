#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//cu transmiterea parametrilor prin valoare
//tipul parametrilor este acelasi ca cel din main
void interschimbarePrinValoare(int nr1, int nr2) {
    int aux = nr1;
    nr1 = nr2;
    nr2 = aux;
}

//cu transmiterea parametrilor prin adresa
void interschimbarePrinPointer(int* nr1, int* nr2) {
    //dereferentiere
    int aux = *nr1;
    *nr1 = *nr2;
    *nr2 = aux;
}

void citireDeLaTastatura(int** vector, int* dimensiuneVector) { //** pentru ca este dinamic si transimtem prin pointer
    printf("\n Dimensiune: ");
    scanf("%d", dimensiuneVector); // de obicei la scanf trebuie adresa, adica punem &, dar aici dimnesiuneVector este deja o adresa ptc are *

    *vector = (int*)malloc((*dimensiuneVector) * sizeof(int)); //alocare dinamica

    for (int i = 0; i < (*dimensiuneVector); i++) { //parantezele sunt necesare pentru ca indexarea are prioritate
        printf("vector[%i] = ", i);
        scanf("%d", &(*vector)[i]); // & ptc avem nevoie de adresa datorita lui scanf, (*) ptc trebuie sa dereferentiem vectorul
        //scanf("%d", *vector + i); //echivalent cu randul de mai sus  
    }
}

void afisare(int* vector, int dimensiuneVector) {
    for (int i = 0; i < dimensiuneVector; i++) {
        printf("\n vector[%d]=%d ", i, vector[i]);
    }
}

int main() {
    int numarIntreg;
    char caracter;
    float numarReal;
    numarIntreg = 7;
    caracter = 'A';
    numarReal = 70.5f;

    printf("%d \n", numarIntreg);
    printf("c \n", caracter);
    printf("%.2f \n", numarReal); //doua zecimale 

    // + - 32 ascii pentru transformare

    //alocare dinamica sau nu

    //sir normal

    char sirCaractere[8]; //pe ultima pozitie e \0 terminator de sir
    for (int i = 0; i < 8; i++) {
        sirCaractere[i] = 97 + i; //de la a la h
    }
    sirCaractere[7] = '\0';

    printf("%s \n", sirCaractere);


    // sir alocat dinamic

    char* sirAlocatDinamic;
    sirAlocatDinamic = (char*)malloc(6 * sizeof(char)); //de preferat sa fie pus chiar daca sizeof(char) e 1
    for (int i = 0; i < 6; i++) {
        sirAlocatDinamic[i] = 65 + i; //de la A la E
    }
    sirAlocatDinamic[5] = '\0';
    printf("%s \n", sirAlocatDinamic);

    //interschimbarea a doua numere

    int var1 = 1, var2 = 10;
    interschimbarePrinValoare(var1, var2); // nu se modifica nimic, folosim doar la afisare cand nu modificam cu nimic variabilele
    interschimbarePrinPointer(&var1, &var2); //& este procesul invers de dereferentiere

    printf("\n var = %d, var2 = %d", var1, var2);

    //citirea de la tastatura a unui vector
    int* vector; //alocat dinamic
    int dimensiuneVector;
    citireDeLaTastatura(&vector, &dimensiuneVector);

    afisare(vector, dimensiuneVector); //prin valoare
}