#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mobila {
    int id;
    int nrArticol;
    char* denumire;
    float pret;
    char culoare;
} Mobila;

typedef struct Nod {
    Mobila info;
    struct Nod* next;
} Nod;

Nod* creareNod(Mobila m) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info.id = m.id;
    nou->info.nrArticol = m.nrArticol;
    nou->info.pret = m.pret;
    nou->info.culoare = m.culoare;
    nou->info.denumire = (char*)malloc(strlen(m.denumire) + 1);
    strcpy(nou->info.denumire, m.denumire);
    nou->next = NULL;
    return nou;
}

void stergeNodPozitie(Nod** cap, int pozitie) {
    if (*cap == NULL) return;
    Nod* temp = *cap;

    if (pozitie == 0) {
        *cap = temp->next;
        free(temp->info.denumire);
        free(temp);
        return;
    }

    Nod* prev = NULL;
    for (int i = 0; temp != NULL && i < pozitie; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp->info.denumire);
    free(temp);
}

void inserareSortata(Nod** cap, Mobila m) {
    Nod* nou = creareNod(m);
    if (*cap == NULL || (*cap)->info.pret >= m.pret) {
        nou->next = *cap;
        *cap = nou;
        return;
    }

    Nod* temp = *cap;
    while (temp->next != NULL && temp->next->info.pret < m.pret) {
        temp = temp->next;
    }
    nou->next = temp->next;
    temp->next = nou;
}

Mobila* salvareInVector(Nod* cap, int* nrElemente) {
    *nrElemente = 0;
    Nod* temp = cap;

    while (temp) {
        if (temp->info.pret > 1000) {
            (*nrElemente)++;
        }
        temp = temp->next;
    }

    if (*nrElemente == 0) return NULL;

    Mobila* vector = (Mobila*)malloc((*nrElemente) * sizeof(Mobila));
    temp = cap;
    int i = 0;
    while (temp) {
        if (temp->info.pret > 1000) {
            vector[i].id = temp->info.id;
            vector[i].nrArticol = temp->info.nrArticol;
            vector[i].pret = temp->info.pret;
            vector[i].culoare = temp->info.culoare;
            vector[i].denumire = (char*)malloc(strlen(temp->info.denumire) + 1);
            strcpy(vector[i].denumire, temp->info.denumire);
            i++;
        }
        temp = temp->next;
    }
    return vector;
}

void interschimbareElemente(Nod* cap, int poz1, int poz2) {
    if (cap == NULL || poz1 == poz2) return;

    Nod* p1 = cap, * p2 = cap;
    for (int i = 0; i < poz1 && p1 != NULL; i++) p1 = p1->next;
    for (int i = 0; i < poz2 && p2 != NULL; i++) p2 = p2->next;

    if (p1 == NULL || p2 == NULL) return;

    Mobila temp = p1->info;
    p1->info = p2->info;
    p2->info = temp;
}

void afisareLista(Nod* cap) {
    while (cap) {
        printf("ID: %d, Articol: %d, Denumire: %s, Pret: %.2f, Culoare: %c\n", cap->info.id, cap->info.nrArticol, cap->info.denumire, cap->info.pret, cap->info.culoare);
        cap = cap->next;
    }
}

int main() {
    Nod* lista = NULL;
    Mobila m1 = { 1, 101, "Scaun", 500.0, 'R' };
    Mobila m2 = { 2, 102, "Masa", 1500.0, 'B' };
    Mobila m3 = { 3, 103, "Dulap", 800.0, 'G' };

    inserareSortata(&lista, m1);
    inserareSortata(&lista, m2);
    inserareSortata(&lista, m3);

    printf("Lista initiala:\n");
    afisareLista(lista);

    stergeNodPozitie(&lista, 1);
    printf("Lista dupa stergerea nodului de pe pozitia 1:\n");
    afisareLista(lista);

    int nrElemente;
    Mobila* vector = salvareInVector(lista, &nrElemente);
    printf("Vectorul cu mobile cu pret > 1000:\n");
    for (int i = 0; i < nrElemente; i++) {
        printf("%s - %.2f\n", vector[i].denumire, vector[i].pret);
        free(vector[i].denumire);
    }
    free(vector);

    interschimbareElemente(lista, 0, 1);
    printf("lista dupa interschimbarea elementelor de pe poz 0 si 1:\n");
    afisareLista(lista);

    return 0;
}
