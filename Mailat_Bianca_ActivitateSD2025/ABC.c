//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<malloc.h>
//#include <stdlib.h>
//#include<string.h>
//
//struct PiesaTeatru {
//	char* titlu;
//	int durataMinute;
//	int anPremiera;
//	float popularitate;
//};
//typedef struct PiesaTeatru PiesaTeatru;
//typedef struct Nod Nod;
//
//struct Nod {
//	PiesaTeatru info;
//	Nod* st;
//	Nod* dr;
//};
//
//PiesaTeatru citirePiesaFisier(FILE* f) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, f);
//	char* aux;
//	aux = strtok(buffer, sep);
//	PiesaTeatru p;
//	p.titlu = malloc(strlen(aux) + 1);
//	strcpy_s(p.titlu, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	p.durataMinute = atoi(aux);
//	p.anPremiera = atoi(strtok(NULL, sep));
//	p.popularitate = atof(strtok(NULL, sep));
//	return p;
//};
//
//void afisarePiesa(PiesaTeatru piesa) {
//	printf("Titlu : %s\n", piesa.titlu);
//	printf("Durata:%d\n", piesa.durataMinute);
//	printf("An: %d\n", piesa.anPremiera);
//	printf("popularitate: %.2f\n\n", piesa.popularitate);
//}
//
////inserare dupa titlu 
//void inserare(Nod** arbore, PiesaTeatru piesaNoua) {
//	if (!(*arbore)) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = piesaNoua;
//		nou->dr = NULL;
//		nou->st = NULL;
//		(*arbore) = nou;
//	}
//	else {
//		int comp = strcmp((*arbore)->info.titlu, piesaNoua.titlu);
//		if (comp < 0) {
//			inserare(&(*arbore)->st, piesaNoua);
//		}else if(comp > 0) {
//			inserare(&(*arbore)->dr, piesaNoua);
//		}
//		else {
//			(*arbore)->info = piesaNoua;
//		}
//	}
//}
//
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		inserare(&arbore, citirePiesaFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//void afisareInOrdine(Nod* arbore) {
//	if (arbore) {
//		afisareInOrdine(arbore->st);
//		afisarePiesa(arbore->info);
//		afisareInOrdine(arbore->dr);
//
//	}
//}
//
//
////Implementați o funcție care returnează piesa cu cea mai mare popularitate, folosind deep copy.
//float popularitateMax(Nod* arbore) {
//	float max = arbore->info.popularitate;
//	if (arbore) {
//		if (arbore->info.popularitate > max) {
//			return popularitateMax(arbore->dr);
//		}
//		else if (arbore->info.popularitate < max) {
//			popularitateMax(arbore->st);
//		}
//		else {
//			return arbore->info.popularitate;
//		}
//	}
//	return max;
//}
//
//PiesaTeatru piesaPopMare(Nod* arbore, float popMax) {
//	if (arbore) {
//		if (arbore->info.popularitate == popMax) {
//			PiesaTeatru piesa;
//			piesa.titlu = (char*)malloc(strlen(arbore->info.titlu) + 1);
//			strcpy_s(piesa.titlu, strlen(arbore->info.titlu)+1, arbore->info.titlu);
//			piesa.durataMinute = arbore->info.durataMinute;
//			piesa.anPremiera = arbore->info.anPremiera;
//			piesa.popularitate = arbore->info.popularitate;
//			return piesa;
//		}
//		else if (arbore->info.popularitate > popMax) {
//			return piesaPopMare(arbore->st, popMax);
//		}
//		else {
//			return piesaPopMare(arbore->dr, popMax);
//		}
//	}
//}
//
//PiesaTeatru getPiesaByTitlu(Nod* arbore, const char* titluCautat) {
//	if (arbore) {
//		int comp = strcmp(arbore->info.titlu, titluCautat);
//		if (comp > 0) {
//			return getPiesaByTitlu(arbore->st, titluCautat);
//		}
//		else if (comp < 0) {
//			return getPiesaByTitlu(arbore->dr, titluCautat);
//		}
//		else {
//			PiesaTeatru p;
//			p.titlu = (char*)malloc(strlen(arbore->info.titlu) + 1);
//			strcpy_s(p.titlu, strlen(arbore->info.titlu) + 1, arbore->info.titlu);
//
//			p.durataMinute = arbore->info.durataMinute;
//			p.anPremiera = arbore->info.anPremiera;
//			p.popularitate = arbore->info.popularitate;
//			return p;
//		}
//	}
//}
//
//void dezalocare(Nod** arbore) {
//	if ((*arbore)) {
//		dezalocare(&(*arbore)->dr);
//		dezalocare(&(*arbore)->st);
//		free((*arbore)->info.titlu);
//		free(*arbore);
//		(*arbore) = NULL;
//
//	}
//}
//int main() {
//	Nod* arbore = citireArboreDinFisier("test.txt");
//	afisareInOrdine(arbore);
//	printf("Max: %.2f\n", popularitateMax(arbore));
//	float popMax = popularitateMax(arbore);
//	printf("-------------------------\n");
//	//printf("piesa: %s", piesaPopMare(arbore, popMax));
//
//
//	printf("----------------------------");
//	afisarePiesa(getPiesaByTitlu(arbore, "Hamlet"));
//	dezalocare(&arbore);
//	return 0;
//}