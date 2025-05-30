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
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* st;
	Nod* dr;
};

Masina citireMasinaDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, sep);
	char* aux;
	Masina m;
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(strlen(aux) + 1);
	strpcy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);
	return m;

}

void afisareMasina(Masina masina) {
	printf("id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calcInaltime(Nod* arbore) {
	if (arbore) {
		int inaltimeSt = calcInaltime(arbore->st);
		int inaltimeDr = calcInaltime(arbore->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
	else {
		return 0;
	}
}

int calcGradEchilibru(Nod* arbore) {
	if (arbore) {
		return calcInaltime(arbore->st) - calcInaltime(arbore->dr);
	}
	else {
		return 0;
	}
}

void rotireDreapta(Nod** arbore) {
	Nod* nou = (*arbore)->st;
	(*arbore)->st = nou->dr;
	nou->dr = (*arbore);
	(*arbore) = nou;
}
void rotireStanga(Nod** arbore) {
	Nod* nou = (*arbore)->dr;
	(*arbore)->dr = nou->st;
	nou->st = (*arbore);
	(*arbore) = nou;
}
void adaugaInAVL(Nod** radacina,Masina m) {
	if ((*radacina)) {
		if ((*radacina)->info.id > m.id) {
			adaugaInAVL(&((*radacina)->st),m);
		}
		else if ((*radacina)->info.id < m.id) {
			adaugaInAVL(&((*radacina)->dr),m);
		}

		int grad = calcGradEchilibru(*radacina);
		if (grad == 2) {
			if (&((*radacina)->st) == 1) {
				rotireDreapta(radacina);
			}
			else {
				rotireStanga((*radacina)->st);
				rotireDreapta(radacina);
			}
		}
		if (grad == -2) {
			if (&((*radacina)->dr) == 1) {
				rotireDreapta((*radacina)->dr);
			}
			rotireStanga(radacina);
		}
	}
}