#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI { //Lista Dublu Inlantuita
	Nod* prim;
	Nod* ultim;
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

void inserareLaInceput(Masina masina, LDI* lista) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod)*1);
	nodNou->inf = masina;
	nodNou->prev = NULL;
	nodNou->next = lista->prim;
	if (lista->prim)
	{
		lista->prim->prev = nodNou;
		lista->prim = nodNou;
	}
	else
	{
		lista->prim = nodNou;
		lista->ultim = nodNou;
	}
	
}

void inserareLaFinal(Masina masina, LDI* lista) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod) * 1);
	nodNou->inf = masina;
	nodNou->prev = lista->ultim;
	nodNou->next = NULL;
	if (lista->ultim)
	{
		lista->ultim->next = nodNou;
		lista->ultim = nodNou;
	}
	else
	{
		lista->prim = nodNou;
		lista->ultim = nodNou;
	}
}

void inserareLaPozitie(Masina masina, int pozitie, LDI* lista) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod) * 1);
	nodNou->inf = masina;
	Nod* temp = lista->prim;
	int contor = 0;
	while (temp && contor < pozitie)
	{
		temp = temp->next;
		contor++;
	}
	if (temp)
	{
		nodNou->next = temp;
		nodNou->prev = temp->prev;
		temp->prev = nodNou;
		if (nodNou->prev)
		{
			nodNou->prev->next = nodNou;
		}
		else
		{
			lista->prim = nodNou;
		}
	}
}

void inserareDupaProducator(Masina masina, const char* producator, LDI* lista) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod) * 1);
	nodNou->inf = masina;
	Nod* temp = lista->prim;
	while (temp && strcmp(temp->inf.producator, producator) != 0)
	{
		temp = temp->next;
	}
	if (temp)
	{
		nodNou->next = temp->next;
		nodNou->prev = temp;
		temp->next = nodNou;
		if (nodNou->next)
		{
			nodNou->next->prev = nodNou;
		}
		else
		{
			lista->ultim = nodNou;
		}
	}
}

void traversareLista(LDI lista) {

	while (lista.prim) {
		afisareMasina(lista.prim->inf);
		lista.prim = lista.prim->next;
	}

}

void traversareInversaLista(LDI lista) {

	while (lista.ultim) {
		afisareMasina(lista.ultim->inf);
		lista.ultim = lista.ultim->prev;
	}

}

void numarareLista(LDI lista, int* nrMasini) {

	while (lista.prim) {
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}

}

void dezalocare(LDI* lista) { 
	Nod* copie = lista->prim;
	while (copie)
	{
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void dezalocareDinSfarsitInceput(LDI* lista) {
	while (lista->ultim)
	{
		free(lista->ultim->inf.producator);
		lista->ultim = lista->ultim->prev;
		if (lista->ultim)
		{
			free(lista->ultim->next);
		}
	}
	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

LDI dezalocareLDI(LDI lista) {
	lista.prim->prev = NULL;
	lista.ultim->next = NULL;

	Nod* copie = lista.prim;
	while (copie)
	{
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista.ultim);
	lista.prim = NULL;
	lista.ultim = NULL;
	return lista;
}

void stergereLaFinal(Nod** ultim) {
	if (ultim)
	{
		free((*ultim)->inf.producator);
		*ultim = (*ultim)->prev;
		if (*ultim)
		{
			free((*ultim)->next);
		}
	}
}

void stergereLaInceput(Nod** prim) {
	if (prim)
	{
		free((*prim)->inf.producator);
		*prim = (*prim)->next;
		if (*prim)
		{
			free((*prim)->prev);
		}
	}
}

void stergereLaPozitie(Nod** prim, int pozitie) {
	Nod* temp = *prim;
	int contor = 0;
	while (temp && contor < pozitie)
	{
		temp = temp->next;
		contor++;
	}
	if (temp)
	{
		if (temp->prev)
		{
			temp->prev->next = temp->next;
		}
		if (temp->next)
		{
			temp->next->prev = temp->prev;
		}
		free(temp->inf.producator);
		free(temp);
	}
}

void stergereDupaProducator(Nod** prim, const char* producator) {
	Nod* temp = *prim;
	while (temp && strcmp(temp->inf.producator, producator) != 0)
	{
		temp = temp->next;
	}
	if (temp)
	{
		if (temp->prev)
		{
			temp->prev->next = temp->next;
		}
		if (temp->next)
		{
			temp->next->prev = temp->prev;
		}
		free(temp->inf.producator);
		free(temp);
	}
}

void dezalocare2(LDI* lista) {
	while (lista->ultim)
	{
		stergereLaFinal(&lista->ultim);
	}
	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void conversieLaVector(LDI lista, Masina** vectorMasini) {

		int nrMasini = 0;
		while (lista.prim) {
			(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie); //deep copy
			nrMasini++;
			lista.prim = lista.prim->next;
			//tema sa folosim realloc
		}
	
}

//void traversareListaCirculara(LDI lista) {
//	Nod* temp = lista.prim;
//	while (temp->next != lista.prim) {
//		afisareMasina(temp->inf);
//		temp = temp->next;
//	}
//	afisareMasina(temp->inf);
//}

void traversareListaCirculara(LDI lista) {
	Nod* temp = lista.prim;
	do {
		afisareMasina(temp->inf);
		temp = temp->next;
	
	} while (temp != lista.prim);
}

//interschimbare 2 noduri
void interschimbare(int pozitia1, int pozitia2, LDI* lista) {
	
	Nod* temp1 = lista->prim;
	Nod* temp2 = lista->prim;
	int contor = 0;
	while (temp1 && contor < pozitia1)
	{
		temp1 = temp1->next;
		contor++;
	}
	contor = 0;
	while (temp2 && contor < pozitia2)
	{
		temp2 = temp2->next;
		contor++;
	}
	if (temp1 && temp2)
	{
		Masina aux = temp1->inf;
		temp1->inf = temp2->inf;
		temp2->inf = aux;
	}
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	printf("\n Afisare masini din lista:");
	inserareLaInceput(initMasina("Dacia", 123), &lista);
	inserareLaInceput(initMasina("BMW", 124), &lista);
	inserareLaInceput(initMasina("Audi", 125), &lista);

	inserareLaFinal(initMasina("Mercedes", 126), &lista);
	inserareLaFinal(initMasina("Ford", 127), &lista);
	printf("\n\n Traversare lista: \n");
	traversareLista(lista);
	//tema traversare de la coada la cap
	printf("\n\n Traversare inversa lista: \n");
	traversareInversaLista(lista);
	int nrMasini = 0;
	numarareLista(lista, &nrMasini);
	printf("\n\n Numarul de masini este %d.", nrMasini);

	printf("\n\n Afisare masini din vector: \n");

	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina)*nrMasini);
	conversieLaVector(lista, &vectorMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].producator);
	}
	free(vectorMasini);

	//inserare la pozitie
	inserareLaPozitie(initMasina("Opel", 128), 2, &lista);
	printf("\n\n Afisare masini dupa inserare la pozitie: \n");
	traversareLista(lista);

	//inserare dupa producator
	inserareDupaProducator(initMasina("Volkswagen", 129), "BMW", &lista);
	printf("\n\n Afisare masini dupa inserare dupa producator: \n");
	traversareLista(lista);

	//interschimbare 2 noduri
	interschimbare(1, 3, &lista);
	printf("\n\n Afisare masini dupa interschimbare: \n");
	traversareLista(lista);

	//LISTA DUBLA CIRCULARA
	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;

	//traversare Lista Dubla Circulara
	printf("\n\n Afisare masini din lista dubla circulara: \n");
	traversareListaCirculara(lista);

	//dezalocare(&lista);
	//lista = dezalocare(lista);
	lista = dezalocareLDI(lista);

	//dezalocareDinSfarsitInceput(&lista);

}