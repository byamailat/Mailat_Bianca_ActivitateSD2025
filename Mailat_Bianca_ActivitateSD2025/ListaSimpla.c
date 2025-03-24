#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>


struct StructuraBiblioteca {
	int id;
	int nrCarti;
	float metripatrati;
	char* nume;
	char* strada;
	unsigned char cod;
};

typedef struct StructuraBiblioteca Biblioteca;
//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Biblioteca info;
	struct Nod* next;
};

typedef struct Nod Nod; //aliasul 


Biblioteca citireBibliotecaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Biblioteca b1;
	aux = strtok(buffer, sep);
	b1.id = atoi(aux);
	b1.nrCarti = atoi(strtok(NULL, sep));
	b1.metripatrati = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);

	b1.nume = malloc(strlen(aux) + 1);
	strcpy(b1.nume, aux);

	aux = strtok(NULL, sep);
	b1.strada = malloc(strlen(aux) + 1);
	strcpy(b1.strada,   aux);

	b1.cod = *strtok(NULL, sep);
	return b1;



}

void afisareBiblioteca(Biblioteca biblioteca) {
	printf("Id: %d\n", biblioteca.id);
	printf("Nr carti: %d\n", biblioteca.nrCarti);
	printf("Metrii patrati: %.2f\n", biblioteca.metripatrati);
	printf("Nume biblioteca: %s\n", biblioteca.nume);
	printf("Strada: %s\n", biblioteca.strada);
	printf("Cod: %c \n\n", biblioteca.cod);
}

void afisareListaBiblioteci(Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()

	while (cap) {
		        afisareBiblioteca(cap->info);
		        cap = cap->next;
		    }

}

void adaugaBibliotecaInLista(/*lista de masini*/ Nod** cap, Biblioteca bibliotecaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));   //creez un nod nou
	nou->info = bibliotecaNoua;   //shallow copy
	nou->next = NULL; //pt ca este ultimul in lista
	if (*cap) {
		Nod* p= *cap; //am luat un nou ptr cu care ma voi deplasa la adrese
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;  //ptr ca nou oricum avea adresa noului nod
	}
	//else-daca nu exista cap, adica este =0
	else {
		*cap = nou;
	}
	
}

void adaugaLaInceputInLista(/*lista de masini*/ Nod* *cap,Biblioteca bibliotecaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = bibliotecaNoua;
	nou->next = (*cap);

	*cap = nou;   //ii dau adresa primului nod


}

Nod* citireListaBiblioteciDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	    Nod* cap = NULL;
	
	    while (!feof(f)) {
	        Biblioteca b = citireBibliotecaDinFisier(f);
	        adaugaBibliotecaInLista(&cap, b);
	    }
	    fclose(f);
	    return (void*)cap;
}

void dezalocareListaMasini(/*lista de masini*/Nod** cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while (*cap) {
		        Nod* p = (*cap);
		        (*cap) = (*cap)->next;
		        free(p->info.nume);
		        free(p->info.strada);
		        free(p);
		    }


}

float calculeazaPretMediu(/*lista de masini*/Nod* cap) {
	//calculeaza pretul mediu al masinilor din lista.


	float suma = 0;
	    int k = 0;
	    while (cap) {
	        suma += cap->info.nrCarti;
	        k++;
	        cap = cap->next;
	    }
	    return (k > 0) ? suma / k : 0;
	return 0;
}

void stergeBiblioteciCuCodul(Nod** cap, char codCautat) {
    while (*cap && (*cap)->info.cod == codCautat) {
        Nod* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.nume);
        free(temp->info.strada);
        free(temp);
    }
    Nod* curent = *cap;
    while (curent && curent->next) {
        if (curent->next->info.cod == codCautat)
        {
            Nod* temp = curent->next;
            curent->next = curent->next->next;
            free(temp->info.nume);
            free(temp->info.strada);
            free(temp);
        }
        else
        {
            curent = curent->next;
        }
    }
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	    Nod* biblioteci = (Nod*)citireListaBiblioteciDinFisier("biblioteci.txt");

	afisareListaBiblioteci(biblioteci);

	printf("nr carti mediu: %.2f\n", calculeazaPretMediu(biblioteci));

	stergeBiblioteciCuCodul(&biblioteci, 'C');
    
    printf("----------DUPA STERGERE-----------\n");
	afisareListaBiblioteci(biblioteci);



	dezalocareListaMasini(&biblioteci);

	return 0;
}