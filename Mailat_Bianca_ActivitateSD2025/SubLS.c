//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <stdlib.h>
//#include <string.h>
//struct Moneda {
//	char* taraEmitenta;
//	int valNominala;
//	float greutate;
//	int anEmitere;
//};
//typedef struct Moneda Moneda;
//
//struct Nod {
//	Moneda info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//Moneda citireMonedaDinFisier(FILE* f) {
//	char buffer[100];
//	char sep[3] = ",;\n";
//	fgets(buffer, 100, f);
//	char* aux = strtok(buffer, sep);
//	Moneda m1;
//	m1.taraEmitenta = malloc(strlen(aux) + 1);
//	strcpy(m1.taraEmitenta, aux);
//	aux = strtok(NULL, sep);
//	m1.valNominala = atoi(aux);
//	aux = strtok(NULL, sep);
//	m1.greutate = atof(aux);
//	aux = strtok(NULL, sep);
//	m1.anEmitere = atoi(aux);
//	return m1;
//}
//
//
//void afisareMoneda(Moneda m) {
//	printf("Tara emitenta: %s\n", m.taraEmitenta);
//	printf("Valoare nominala: %d\n", m.valNominala);
//	printf("Greutate : %.2f\n", m.greutate);
//	printf("An emitere: %d\n\n", m.anEmitere);
//}
//
//
//void afisareListaMoneda(Nod* cap) {
//	if (cap) {
//		Nod* p = cap;
//		while (p) {
//			afisareMoneda(cap->info);
//			p = p->next;
//		}
//	}
//}
//
//
//void adaugaMonedaLaSfarsit(Nod** cap, Moneda monedaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = monedaNoua;
//	nou->next = NULL;
//	if (*cap) {
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
//void adaugaMonedaInceput(Nod** cap, Moneda monedaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = monedaNoua;
//	nou->next=(*cap);
//
//	if (*cap != NULL) {
//		Nod* p = *cap;
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		*cap = nou;
//	}
//	else {
//		*cap = nou;
//	}
//
//}
//
//
//Nod* citireListaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* cap = NULL;
//
//	while (!feof(f)) {
//		adaugaMonedaLaSfarsit(&cap, citireMonedaDinFisier(f));
//	}
//
//	fclose(f);
//	return cap;
//}
//
//
//void dezalocare(Nod** cap) {
//	Nod* p = *cap;
//	while (p) {
//		Nod* aux = p;
//		p = p->next;
//
//		if (aux->info.taraEmitenta) {
//			free(aux->info.taraEmitenta);
//		}
//		free(aux);
//	}
//	*cap = NULL;
//}
//
//
//int main() {
//	Nod* m = (Nod*)citireListaDinFisier("monede.txt");
//	
//	afisareListaMoneda(m);
//
//	dezalocare(&m);
//	return 0;
//}