#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int nrSectii;
    float suprafata;
    char* nume;
    char* adresa;
    char categorie;
} Biblioteca;

Biblioteca creaBiblioteca(int id, int nrSectii, float suprafata,
    const char* nume, const char* adresa,
    char categorie)
{
    Biblioteca b;
    b.id = id;
    b.nrSectii = nrSectii;
    b.suprafata = suprafata;
    b.nume = malloc(strlen(nume) + 1);
    strcpy(b.nume, nume);
    b.adresa = malloc(strlen(adresa) + 1);
    strcpy(b.adresa, adresa);
    b.categorie = categorie;
    return b;
}

void dezalocaBiblioteca(Biblioteca* b) {
    free(b->nume);
    free(b->adresa);
}


typedef struct {
    Biblioteca* elems;  
    int vf;            
    int capacitate;   
} StivaVector;

void initStivaVector(StivaVector* s, int capacitate) {
    s->elems = malloc(sizeof(Biblioteca) * capacitate);
    s->vf = -1;
    s->capacitate = capacitate;
}

int esteGoalaStivaVector(const StivaVector* s) {
    return s->vf == -1;
}

int estePlinaStivaVector(const StivaVector* s) {
    return s->vf + 1 == s->capacitate;
}

void pushStivaVector(StivaVector* s, Biblioteca b) {
    if (estePlinaStivaVector(s)) {
        printf("Eroare: stiva vector este plină!\n");
        return;
    }
    s->elems[++s->vf] = creaBiblioteca(
        b.id, b.nrSectii, b.suprafata, b.nume, b.adresa, b.categorie);
}

Biblioteca popStivaVector(StivaVector* s) {
    if (esteGoalaStivaVector(s)) {
        return creaBiblioteca(-1, 0, 0.0f, "", "", ' ');
    }
    Biblioteca rez = s->elems[s->vf--];
    return rez;
}

void elibereazaStivaVector(StivaVector* s) {
    while (!esteGoalaStivaVector(s)) {
        Biblioteca b = popStivaVector(s);
        dezalocaBiblioteca(&b);
    }
    free(s->elems);
    s->elems = NULL;
}
//lifo
typedef struct NodSimplu {
    Biblioteca info;
    struct NodSimplu* next;
} NodSimplu;

typedef struct {
    NodSimplu* vf;   
} StivaListaSimpla;

void initStivaLista(StivaListaSimpla* s) {
    s->vf = NULL;
}

int esteGoalaStivaLista(const StivaListaSimpla* s) {
    return s->vf == NULL;
}

void pushStivaLista(StivaListaSimpla* s, Biblioteca b) {
    NodSimplu* nou = malloc(sizeof(NodSimplu));
    nou->info = creaBiblioteca(
        b.id, b.nrSectii, b.suprafata, b.nume, b.adresa, b.categorie);
    nou->next = s->vf;
    s->vf = nou;
}

Biblioteca popStivaLista(StivaListaSimpla* s) {
    if (esteGoalaStivaLista(s)) {
        return creaBiblioteca(-1, 0, 0.0f, "", "", ' ');
    }
    NodSimplu* temp = s->vf;
    Biblioteca rez = temp->info;
    s->vf = temp->next;
    free(temp);
    return rez;
}

void elibereazaStivaLista(StivaListaSimpla* s) {
    while (!esteGoalaStivaLista(s)) {
        Biblioteca b = popStivaLista(s);
        dezalocaBiblioteca(&b);
    }
}


typedef struct NodDublu {
    Biblioteca info;
    struct NodDublu* next;
    struct NodDublu* prev;
} NodDublu;

typedef struct {
    NodDublu* vf;   
} StivaListaDubla;

void initStivaDubla(StivaListaDubla* s) {
    s->vf = NULL;
}

int esteGoalaStivaDubla(const StivaListaDubla* s) {
    return s->vf == NULL;
}

void pushStivaDubla(StivaListaDubla* s, Biblioteca b) {
    NodDublu* nou = malloc(sizeof(NodDublu));
    nou->info = creaBiblioteca(
        b.id, b.nrSectii, b.suprafata, b.nume, b.adresa, b.categorie);
    nou->next = s->vf;
    nou->prev = NULL;
    if (s->vf)
        s->vf->prev = nou;
    s->vf = nou;
}

Biblioteca popStivaDubla(StivaListaDubla* s) {
    if (esteGoalaStivaDubla(s)) {
        return creaBiblioteca(-1, 0, 0.0f, "", "", ' ');
    }
    NodDublu* temp = s->vf;
    Biblioteca rez = temp->info;
    s->vf = temp->next;
    if (s->vf)
        s->vf->prev = NULL;
    free(temp);
    return rez;
}

void elibereazaStivaDubla(StivaListaDubla* s) {
    while (!esteGoalaStivaDubla(s)) {
        Biblioteca b = popStivaDubla(s);
        dezalocaBiblioteca(&b);
    }
}
void afisareBiblioteca(const Biblioteca b) {
    printf("Id: %d\n", b.id);
    printf("Nr. sectii: %d\n", b.nrSectii);
    printf("Suprafata: %.2f m^2\n", b.suprafata);
    printf("Nume: %s\n", b.nume);
    printf("Adresa: %s\n", b.adresa);
    printf("Categorie: %c\n\n", b.categorie);
}

int main() {
    StivaVector sv;
    initStivaVector(&sv, 10);
    Biblioteca b1 = creaBiblioteca(1, 4, 50.0f, "Centrala", "Strada X", 'C');
    pushStivaVector(&sv, b1);
    pushStivaVector(&sv, creaBiblioteca(2, 8, 75.0f, "Municipala", "Strada Y", 'D'));
    Biblioteca extr1 = popStivaVector(&sv);
    afisareBiblioteca(extr1);
    dezalocaBiblioteca(&extr1);
    elibereazaStivaVector(&sv);
    dezalocaBiblioteca(&b1);

    StivaListaSimpla sl;
    initStivaLista(&sl);
    pushStivaLista(&sl, creaBiblioteca(3, 6, 40.0f, "Orașeneasca", "Strada Z", 'C'));
    Biblioteca extr2 = popStivaLista(&sl);
    afisareBiblioteca(extr2);
    dezalocaBiblioteca(&extr2);
    elibereazaStivaLista(&sl);

    StivaListaDubla sd;
    initStivaDubla(&sd);
    pushStivaDubla(&sd, creaBiblioteca(4, 5, 60.0f, "Rurala", "Strada W", 'D'));
    Biblioteca extr3 = popStivaDubla(&sd);
    afisareBiblioteca(extr3);
    dezalocaBiblioteca(&extr3);
    elibereazaStivaDubla(&sd);

    return 0;
}
