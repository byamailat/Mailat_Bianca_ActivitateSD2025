//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    int id;
//    int nrSectii;         
//    float suprafata;      
//    char* nume;          
//    char* adresa;        
//    char categorie;       
//} Biblioteca;
//
//typedef struct Nod {
//    Biblioteca info;
//    struct Nod* stanga;
//    struct Nod* dreapta;
//} Nod;
//
//typedef struct {
//    Biblioteca* vector;
//    int dim;
//    int capacitate;
//} VectorBiblioteci;
//
//typedef struct NodListSimpla {
//    Biblioteca info;
//    struct NodListSimpla* next;
//} NodListSimpla;
//
//typedef struct NodListaDubla {
//    Biblioteca info;
//    struct NodListaDubla* next;
//    struct NodListaDubla* prev;
//} NodListaDubla;
//
//Biblioteca creareBiblioteca(int id, int nrSectii, float suprafata,
//    const char* nume, const char* adresa,
//    char categorie)
//{
//    Biblioteca b;
//    b.id = id;
//    b.nrSectii = nrSectii;
//    b.suprafata = suprafata;
//    b.nume = malloc(strlen(nume) + 1);
//    strcpy(b.nume, nume);
//    b.adresa = malloc(strlen(adresa) + 1);
//    strcpy(b.adresa, adresa);
//    b.categorie = categorie;
//    return b;
//}
//
//void afisareBiblioteca(const Biblioteca b) {
//    printf("Id: %d\n", b.id);
//    printf("Nr. secții: %d\n", b.nrSectii);
//    printf("Suprafață: %.2f m^2\n", b.suprafata);
//    printf("Nume: %s\n", b.nume);
//    printf("Adresă: %s\n", b.adresa);
//    printf("Categorie: %c\n\n", b.categorie);
//}
//
//void dezalocareBiblioteca(Biblioteca* b) {
//    free(b->nume);
//    free(b->adresa);
//}
//
//int inaltime(Nod* rad) {
//    if (!rad) return 0;
//    int hL = inaltime(rad->stanga);
//    int hR = inaltime(rad->dreapta);
//    return 1 + (hL > hR ? hL : hR);
//}
//
//int gradEchilibru(Nod* rad) {
//    return inaltime(rad->stanga) - inaltime(rad->dreapta);
//}
//
//void rotireStanga(Nod** rad) {
//    Nod* p = *rad;
//    Nod* q = p->dreapta;
//    p->dreapta = q->stanga;
//    q->stanga = p;
//    *rad = q;
//}
//
//void rotireDreapta(Nod** rad) {
//    Nod* p = *rad;
//    Nod* q = p->stanga;
//    p->stanga = q->dreapta;
//    q->dreapta = p;
//    *rad = q;
//}
//
//void inserareAVL(Nod** rad, Biblioteca b) {
//    if (!*rad) {
//        *rad = malloc(sizeof(Nod));
//        (*rad)->info = creareBiblioteca(
//            b.id, b.nrSectii, b.suprafata,
//            b.nume, b.adresa, b.categorie);
//        (*rad)->stanga = (*rad)->dreapta = NULL;
//    }
//    else if (b.id < (*rad)->info.id) {
//        inserareAVL(&(*rad)->stanga, b);
//    }
//    else {
//        inserareAVL(&(*rad)->dreapta, b);
//    }
//
//    int fb = gradEchilibru(*rad);
//    if (fb == 2) {
//        if (gradEchilibru((*rad)->stanga) < 0)
//            rotireStanga(&(*rad)->stanga);
//        rotireDreapta(rad);
//    }
//    else if (fb == -2) {
//        if (gradEchilibru((*rad)->dreapta) > 0)
//            rotireDreapta(&(*rad)->dreapta);
//        rotireStanga(rad);
//    }
//}
//
//Biblioteca cautaBibliotecaDupaID(Nod* rad, int id) {
//    if (!rad) return (Biblioteca) { -1, 0, 0.0f, NULL, NULL, '\0' };
//    if (id < rad->info.id)
//        return cautaBibliotecaDupaID(rad->stanga, id);
//    else if (id > rad->info.id)
//        return cautaBibliotecaDupaID(rad->dreapta, id);
//    else
//        return rad->info;
//}
//
//void dezalocareArbore(Nod** rad) {
//    if (*rad) {
//        dezalocareArbore(&(*rad)->stanga);
//        dezalocareArbore(&(*rad)->dreapta);
//        dezalocareBiblioteca(&(*rad)->info);
//        free(*rad);
//        *rad = NULL;
//    }
//}
//
//void initializareVector(VectorBiblioteci* v, int capacitate) {
//    v->vector = malloc(sizeof(Biblioteca) * capacitate);
//    v->dim = 0;
//    v->capacitate = capacitate;
//}
//
//void adaugaInVector(VectorBiblioteci* v, Biblioteca b) {
//    if (v->dim < v->capacitate) {
//        v->vector[v->dim++] = creareBiblioteca(
//            b.id, b.nrSectii, b.suprafata,
//            b.nume, b.adresa, b.categorie);
//    }
//}
//
//void afisareVector(const VectorBiblioteci v) {
//    for (int i = 0; i < v.dim; i++)
//        afisareBiblioteca(v.vector[i]);
//}
//
//void dezalocareVector(VectorBiblioteci* v) {
//    for (int i = 0; i < v->dim; i++)
//        dezalocareBiblioteca(&v->vector[i]);
//    free(v->vector);
//    v->vector = NULL;
//}
//
//void salvareVectorPreordine(Nod* rad, VectorBiblioteci* v) {
//    if (!rad) return;
//    adaugaInVector(v, rad->info);
//    salvareVectorPreordine(rad->stanga, v);
//    salvareVectorPreordine(rad->dreapta, v);
//}
//
//void salvareVectorInordine(Nod* rad, VectorBiblioteci* v) {
//    if (!rad) return;
//    salvareVectorInordine(rad->stanga, v);
//    adaugaInVector(v, rad->info);
//    salvareVectorInordine(rad->dreapta, v);
//}
//
//void salvareVectorPostordine(Nod* rad, VectorBiblioteci* v) {
//    if (!rad) return;
//    salvareVectorPostordine(rad->stanga, v);
//    salvareVectorPostordine(rad->dreapta, v);
//    adaugaInVector(v, rad->info);
//}
//
//void adaugaListaSimplaDinArbore(Nod* rad, NodListSimpla** cap) {
//    if (!rad) return;
//    if (!*cap) {
//        *cap = malloc(sizeof(NodListSimpla));
//        (*cap)->info = creareBiblioteca(
//            rad->info.id, rad->info.nrSectii,
//            rad->info.suprafata, rad->info.nume,
//            rad->info.adresa, rad->info.categorie);
//        (*cap)->next = NULL;
//    }
//    else {
//        NodListSimpla* t = *cap;
//        while (t->next) t = t->next;
//        t->next = malloc(sizeof(NodListSimpla));
//        t->next->info = creareBiblioteca(
//            rad->info.id, rad->info.nrSectii,
//            rad->info.suprafata, rad->info.nume,
//            rad->info.adresa, rad->info.categorie);
//        t->next->next = NULL;
//    }
//    adaugaListaSimplaDinArbore(rad->stanga, cap);
//    adaugaListaSimplaDinArbore(rad->dreapta, cap);
//}
//
//void afisareListaSimpla(NodListSimpla* cap) {
//    while (cap) {
//        afisareBiblioteca(cap->info);
//        cap = cap->next;
//    }
//}
//
//void dezalocareListaSimpla(NodListSimpla** cap) {
//    while (*cap) {
//        NodListSimpla* tmp = *cap;
//        *cap = tmp->next;
//        dezalocareBiblioteca(&tmp->info);
//        free(tmp);
//    }
//}
//
//void adaugaListaDublaDinArbore(Nod* rad, NodListaDubla** cap) {
//    if (!rad) return;
//    if (!*cap) {
//        *cap = malloc(sizeof(NodListaDubla));
//        (*cap)->info = creareBiblioteca(
//            rad->info.id, rad->info.nrSectii,
//            rad->info.suprafata, rad->info.nume,
//            rad->info.adresa, rad->info.categorie);
//        (*cap)->next = (*cap)->prev = NULL;
//    }
//    else {
//        NodListaDubla* t = *cap;
//        while (t->next) t = t->next;
//        t->next = malloc(sizeof(NodListaDubla));
//        t->next->info = creareBiblioteca(
//            rad->info.id, rad->info.nrSectii,
//            rad->info.suprafata, rad->info.nume,
//            rad->info.adresa, rad->info.categorie);
//        t->next->prev = t;
//        t->next->next = NULL;
//    }
//    adaugaListaDublaDinArbore(rad->stanga, cap);
//    adaugaListaDublaDinArbore(rad->dreapta, cap);
//}
//
//void afisareListaDubla(NodListaDubla* cap) {
//    while (cap) {
//        afisareBiblioteca(cap->info);
//        cap = cap->next;
//    }
//}
//
//void dezalocareListaDubla(NodListaDubla** cap) {
//    while (*cap) {
//        NodListaDubla* tmp = *cap;
//        *cap = tmp->next;
//        dezalocareBiblioteca(&tmp->info);
//        free(tmp);
//    }
//}
//
//int main() {
//    Nod* radacina = NULL;
//
//    Biblioteca biblioteci[] = {
//        creareBiblioteca(1,  4, 34.5f, "Mihai",    "Strada A", 'C'),
//        creareBiblioteca(2, 10, 50.0f, "Eminescu","Strada B", 'D'),
//        creareBiblioteca(3,  8, 42.3f, "Creanga", "Strada C", 'C'),
//        creareBiblioteca(4, 15, 60.2f, "Caragiale","Strada D", 'C'),
//        creareBiblioteca(5, 20, 75.8f, "Sadoveanu","Strada E", 'D'),
//        creareBiblioteca(6, 12, 55.4f, "Rebreanu","Strada F", 'D'),
//        creareBiblioteca(7, 30, 90.1f, "Blaga",   "Strada G", 'D'),
//        creareBiblioteca(8, 25, 80.0f, "Arghezi", "Strada H", 'D'),
//        creareBiblioteca(9, 18, 65.7f, "Slavici", "Strada I", 'C'),
//        creareBiblioteca(10, 22, 70.5f, "Vlahuta", "Strada J", 'D')
//    };
//
//    for (int i = 0; i < 10; i++)
//        inserareAVL(&radacina, biblioteci[i]);
//
//    VectorBiblioteci v;
//    initializareVector(&v, 20);
//    salvareVectorPreordine(radacina, &v);
//    afisareVector(v);
//    dezalocareVector(&v);
//
//    NodListSimpla* listaS = NULL;
//    adaugaListaSimplaDinArbore(radacina, &listaS);
//    afisareListaSimpla(listaS);
//    dezalocareListaSimpla(&listaS);
//
//    NodListaDubla* listaD = NULL;
//    adaugaListaDublaDinArbore(radacina, &listaD);
//    afisareListaDubla(listaD);
//    dezalocareListaDubla(&listaD);
//
//    Biblioteca gasita = cautaBibliotecaDupaID(radacina, 5);
//    if (gasita.id != -1) afisareBiblioteca(gasita);
//    else               printf("Nu a fost gasit");
//
//    for (int i = 0; i < 10; i++)
//        dezalocareBiblioteca(&biblioteci[i]);
//    dezalocareArbore(&radacina);
//
//    return 0;
//}
