//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//#include <stdlib.h>
//
//
//struct Biblioteca {
//	int id;
//	int nrCarti;
//	float metripatrati;
//	char* nume;
//	char* strada;
//	unsigned char cod;
//};
//typedef struct Biblioteca Biblioteca;
//
//struct Nod {
//	Biblioteca info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//
//Biblioteca citireBibliotecaDinFisier(FILE* file) {
//	Biblioteca b;
//	char buffer[100];
//	char sep[3] = ",;\n";
//
//	fgets(buffer, 100, file);
//	char* aux;
//	aux = strtok(buffer, sep);
//	b.id = atoi(aux);
//	b.nrCarti = atoi(strtok(NULL, sep));
//	b.metripatrati = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	b.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(b.nume, aux);
//	aux = strtok(NULL, sep);
//	b.strada = (char*)malloc(strlen(aux) + 1);
//	strcpy(b.strada, aux);
//	char* token = strtok(NULL, sep);
//	if (token != NULL) {
//		b.cod = (unsigned char)token[0];
//	}
//	return b;
//
//}
//
//void afisareBiblioteca(Biblioteca biblioteca) {
//	printf("id: %d \n", biblioteca.id);
//	printf("nrCarti: %d \n", biblioteca.nrCarti);
//	printf("metri patrati: %.2f \n", biblioteca.metripatrati);
//	printf("Nume: %s \n", biblioteca.nume);
//	printf("strada: %s \n", biblioteca.strada);
//	printf("cod: %c \n\n", biblioteca.cod);
//
//}
//
//void afisareLista(Nod* cap) {
//	while (cap != NULL) {
//		afisareBiblioteca(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaBibliotecaInLista(Nod** cap, Biblioteca bibliotecaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = bibliotecaNoua;
//	nou->next = NULL;
//	if (*cap != NULL) {
//		Nod* p = *cap;
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//	else {
//		*cap = nou;
//	}
//}
//
//void adaugaLaInceput(Nod** cap, Biblioteca bibliotecaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = bibliotecaNoua;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//Nod* citireLista(const char* numeFisier) {
//	Nod* cap = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	if (f!=NULL) {
//		
//		while (!feof(f)) {
//			adaugaBibliotecaInLista(&cap, citireBibliotecaDinFisier(f));
//
//		}
//	}
//	fclose(f);
//	return cap;
//}
//
//void dezalocare(Nod** cap) {
//	while (*cap != NULL) {
//		Nod* p = *cap;
//		(*cap) = p->next;
//		if (p->info.nume) {
//			free(p->info.nume);
//		}
//		if (p->info.strada) {
//			free(p->info.strada);
//		}
//		free(p);
//	}
//}
//
//
//int main() {
//	Nod* cap = citireLista("biblioteci.txt");
//	afisareLista(cap);
//	dezalocare(&cap);
//
//
//
//	return 0;
//}