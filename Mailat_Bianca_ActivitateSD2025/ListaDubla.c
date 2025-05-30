//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include<string.h>
//
//
//struct Masina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct Masina Masina;
//struct Nod {
//	Masina info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//
//struct ListaDubla {
//	Nod* first;
//	Nod* last;
//	int nrNoduri;
//};
//typedef struct ListaDubla ListaDubla;
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",;\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi: %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie : %c\n\n", masina.serie);
//
//}
//
//void afisareListaMasiniInceput(ListaDubla listaDubla) {
//	Nod* p = listaDubla.first;
//
//	while (p != NULL) {
//		afisareMasina(p->info);
//		p = p->next;
//	}
//}
//
//void afisareMasinaSfarsit(ListaDubla listaDubla) {
//	Nod* p = listaDubla.last;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//
//
//void adaugaMasinaInLista(ListaDubla* listaDubla, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = listaDubla->last;
//	if (listaDubla->last != NULL) {
//		listaDubla->last->next = nou;
//
//	}
//	else {
//		listaDubla->first = nou;
//
//	}
//	listaDubla->last = nou;
//	listaDubla->nrNoduri++;
//
//}
//
//void adaugaLaInceputInLista(ListaDubla* listaDubla, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua; //shallow copy
//	nou->next = listaDubla->first;
//	nou->prev = NULL;
//	if (listaDubla->first != NULL) {
//		listaDubla->first->prev = nou;
//
//	}
//	else {
//		listaDubla->last = nou;
//	}
//	listaDubla->first = nou;
//	listaDubla->nrNoduri++;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	ListaDubla lista;
//	lista.first = NULL;
//	lista.last = NULL;
//	lista.nrNoduri=0;
//	while (!feof(f)) {
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//
//
//void dezalocare(ListaDubla* lista) {
//	Nod* p = lista->first;  //pornim de la inceputul listei
//	while (p) {
//		Nod* aux = p;
//		p = p->next;
//		if (aux->info.model) {
//			free(aux->info.model);
//		}if (aux->info.numeSofer) {
//			free(aux->info.numeSofer);
//		}free(aux);
//	}
//	lista->first = NULL;
//	lista->last = NULL;
//	lista->nrNoduri = 0;
//}
//
//
//float calculeazaPretMediu(ListaDubla listaDubla) {
//	float suma = 0;
//	Nod* p = listaDubla.first;
//	if (listaDubla.nrNoduri > 0) {
//		p = p->next;
//		while (p) {
//			suma += p->info.pret;
//			p = p->next;
//		}
//		return suma / listaDubla.nrNoduri;
//	}return 0;
//}
//
//
//char* getNumeSoferMasinaScumpa(ListaDubla lista) {
//	if (lista.first) {
//		Nod* max = lista.first;
//		Nod* p = lista.first->next;
//		while (p) {
//			if (p->info.pret > max->info.pret) {
//				max = p;
//			}p = p->next;
//		}
//		char* nume = (char*)malloc(strlen(max->info.numeSofer) + 1);
//		strcpy(nume, max->info.numeSofer);
//		return nume;
//	}
//}
//
//int main() {
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt.txt");
//
//	afisareListaMasiniInceput(lista);
//	printf("-----------------\n");
//	afisareMasinaSfarsit(lista);
//	printf("Pretul mediu : %.2f\n ", calculeazaPretMediu(lista));
//	printf("Soferul cu masina cea mai scumpa : %s\n", getNumeSoferMasinaScumpa(lista));
//	dezalocare(&lista);
//	return 0;
//}