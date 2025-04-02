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


struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;
//creare structura pentru un nod dintr-o lista simplu inlantuita

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** vector;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(/*lista de masini*/Nod* cap) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;

	}
}

void adaugaMasinaInLista(/*lista de masini*/ Nod* cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;

	while (cap->next) {
		cap = cap->next;
	
	}
	cap->next = nou;
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(/*atribut al masini pentru clusterizare*/ const char* model,int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	int suma = 0;
	for (int i = 0; i < strlen(model); i++) {
		suma += model[i];

	}return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva

	int poz=calculeazaHash(masina.model, hash.dim);
	if (hash.vector[poz] != NULL) {
		//inseamna ca avem coliziiune daca este indeplinit if ul
		adaugaMasinaInLista(hash.vector[poz], masina);
	}
	else {
		//nu avem coliziune
		hash.vector[poz] = (Nod*)malloc(sizeof(Nod));
		hash.vector[poz]->info = masina;
		hash.vector[poz]->next = NULL;
	}

}

HashTable citireMasiniDinFisier(const char* numeFisier,int dimensiune) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen("masini.txt.txt","r");
	HashTable hash = initializareHashTable(dimensiune);
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f); //mereu cand functia returneaza un ob trb sa l scriem in stanga lui egal
		inserareMasinaInTabela(hash, m);
	}fclose(f);
	return hash;
}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++) {
		printf("\nClusterul %d\n", i);
		afisareListaMasini(ht.vector[i]);
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	return NULL;
}

Masina getMasinaDupaCheie(HashTable ht ,const char* model) {
	int poz = calculeazaHash(model, ht.dim);
	Masina masina;
	masina.id = -1;
	if (ht.vector[poz] != NULL) {
		Nod* p = ht.vector[poz];
		while (p != NULL && strcmp(p->info.model, model != 0)) {
			p = p->next;
		}
		if (p != NULL) {
			return p->info;
		}
	}
	return masina;

}

int main() {
	HashTable ht = citireMasiniDinFisier("masini.txt.txt",10);
	afisareTabelaDeMasini(ht);


	printf("Masina de model Astra\n");
	Masina m = getMasinaDupaCheie(ht, "Astra");
	afisareMasina(m);



	return 0;
}