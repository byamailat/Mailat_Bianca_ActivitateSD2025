
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct NodDublu {
	Masina info;
	struct NodDublu* prev;
	struct NodDublu* next;
};
typedef struct NodDublu NodDublu;

struct  Coada
{
	NodDublu* front;
	NodDublu* rear;
};

typedef struct Coada Coada;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, file) == NULL) {
		Masina empty = { -1, 0, 0, NULL, NULL, '-' };
		return empty;
	}
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	aux = strtok(NULL, sep);
	m1.serie = aux[0];
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


Masina extrage(Coada* coada) {
	NodDublu* temp = coada->front;
	Masina m = coada->front->info;
	coada->front = coada->front->next;
	if (coada->front == NULL) {
		coada->rear = NULL;
	}
	else {
		coada->front->prev = NULL;
	}
	free(temp);
	return m;
	
}
void enqueue(Coada* coada, Masina masina) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = masina;
	nou->prev = coada->rear;
	nou->next = NULL;
	if (coada->rear) {
		coada->rear->next = nou;
	}
	else {
		coada->front = nou;
	}
	coada->rear = nou;
}

Masina extrage(Coada* coada) {
	if (coada->front) {
		NodDublu* temp = coada->front;    //ATENTIE- TEMP IL FOLOSESTI DOAR CA SA IL STERGI DUPA. NU UMBLI CU EL.
		Masina m = coada->front->info;
		coada->front = coada->front->next;

		if (coada->front ==NULL) {
			coada->rear = NULL;
		}
		else {
			coada->front->prev = NULL;    //acum primul nod in coada nu are nimic in fata lui 
		}
		free(temp);
		return m;
	}

	else {
		Masina m;
		m.id = -1;
		return m;
	}
}

Coada citireCoadaDinFisier(const char* numefisier) {
	FILE* f = fopen(numefisier, "r");
	Coada coada = { NULL, NULL };
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		enqueue(&coada, m);
	}
	fclose(f);
	return coada;
}

void dezalocare(Coada* coada) {
	while (coada->front) {
		Masina m = extrage(coada);
		free(m.model);
		free(m.numeSofer);
	}
}