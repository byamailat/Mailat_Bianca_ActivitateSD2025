#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* st;
	Nod* dr;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
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



int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
		int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	
	}
	else {
		return 0;
	}
	
}


//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

//rotire la dreapta
//returneaza Nod* pentru ca aunci cand rotim avem o noua radacina 
Nod* rotireDreapta(Nod* radacina) {
	Nod* nod;  //salvam adresa nodului din stanga  
	nod = radacina->st;
	radacina->st = nod->dr;
	nod->dr = radacina;
	return nod;
}


Nod* rotireStanga (Nod* radacina) {
	Nod* aux;
	aux = radacina->dr;
	radacina->dr = aux->st;
	aux->st = radacina;
	return aux;
}

int gradEchilibru(Nod* radacina) {
	int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
	int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);
	return inaltimeDr - inaltimeSt;
}



void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->st), masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->dr), masinaNoua);
		}

		int grad = gradEchilibru((*radacina));
		if (grad == 2) {
			if (gradEchilibru((*radacina)->st) == 1) {
				//LL=>rotire dreapta
				(*radacina) = rotireDreapta((*radacina));
			}
			else {
				(*radacina)->st = rotireStanga((*radacina)->st);
				(*radacina) = rotireDreapta((*radacina));
			}
		}
		else if (grad == -2) {
			if (gradEchilibru((*radacina)->dr) == 1) {
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
				(*radacina) = rotireStanga(*radacina);
			}
			else {
				(*radacina) = rotireStanga((*radacina));
			}
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->st = NULL;
		nou->dr = NULL;
		*radacina = nou;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArboreEchilibrat(&radacina, m);
		
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void dezalocareArboreDeMasini(/*arbore de masini*/Nod** radacina) {

	//sunt dezalocate toate masinile si arborele de elemente
		//sunt dezalocate toate masinile si arborele de elemente
	if ((*radacina) != NULL) {
		dezalocareArboreDeMasini(&((*radacina)->st));
		dezalocareArboreDeMasini(&((*radacina)->dr));
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt.txt");
	printf("Inaltime subarbore stang este:%d", calculeazaInaltimeArbore(arbore->st));


	return 0;
}