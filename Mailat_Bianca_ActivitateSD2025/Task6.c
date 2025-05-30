//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include<malloc.h>
//
//typedef struct Mobila {
//    int id;
//    int nrArticol;
//    char* denumire;
//    float pret;
//    char culoare;
//} Mobila;
//
//
//
//// Nod pentru lista dublu înlănțuită
//typedef struct NodDublu {
//    Mobila info;
//    struct NodDublu* prev;
//    struct NodDublu* next;
//} NodDublu;
//
//// Nod pentru lista simplu înlănțuită
//typedef struct NodSimplu {
//    Mobila info;
//    struct NodSimplu* next;
//} NodSimplu;
//
//// Funcție pentru crearea unui nod nou
//
// NodDublu* creareNod(Mobila m) {
//NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
//nou->info.id = m.id;
//nou->info.nrArticol = m.nrArticol;
//nou->info.pret = m.pret;
//nou->info.culoare = m.culoare;
//nou->info.denumire = (char*)malloc(strlen(m.denumire) + 1);
//strcpy(nou->info.denumire, m.denumire);
//nou->prev = nou->next = NULL;
//return nou;
//}
//
//void stergeNodPozitie(NodDublu** cap, int pozitie) {
//    if (*cap == NULL) return;
//    NodDublu* temp = *cap;
//
//    for (int i = 0; temp != NULL && i < pozitie; i++) {
//        temp = temp->next;
//    }
//
//    if (temp == NULL) return;
//    if (temp->prev != NULL) temp->prev->next = temp->next;
//    if (temp->next != NULL) temp->next->prev = temp->prev;
//    if (temp == *cap) *cap = temp->next;
//
//    free(temp->info.denumire);
//    free(temp);
//}
//
//void inserareSortata(NodDublu** cap, Mobila m) {
//    NodDublu* nou = creareNod(m);
//    if (*cap == NULL) {
//        *cap = nou;
//        return;
//    }
//    NodDublu* temp = *cap;
//    while (temp->next != NULL && temp->next->info.pret < m.pret) {
//        temp = temp->next;
//    }
//    nou->next = temp->next;
//    if (temp->next != NULL) temp->next->prev = nou;
//    temp->next = nou;
//    nou->prev = temp;
//}
//
//void afisareCrescator(NodDublu* cap) {
//    while (cap) {
//        printf("ID: %d, Articol: %d, Denumire: %s, Pret: %.2f, Culoare: %c\n", cap->info.id, cap->info.nrArticol, cap->info.denumire, cap->info.pret, cap->info.culoare);
//        if (cap->next == NULL) break;
//        cap = cap->next;
//    }
//}
//
//void afisareDescrescator(NodDublu* cap) {
//    if (!cap) return;
//    while (cap->next) cap = cap->next;
//    while (cap) {
//        printf("ID: %d, Articol: %d, Denumire: %s, Pret: %.2f, Culoare: %c\n", cap->info.id, cap->info.nrArticol, cap->info.denumire, cap->info.pret, cap->info.culoare);
//        cap = cap->prev;
//    }
//}
//
//NodSimplu* salvareInListaSimpla(NodDublu* cap, float prag) {
//    NodSimplu* capSimplu = NULL;
//    while (cap) {
//        if (cap->info.pret > prag) {
//            NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
//            nou->info.id = cap->info.id;
//            nou->info.nrArticol = cap->info.nrArticol;
//            nou->info.pret = cap->info.pret;
//            nou->info.culoare = cap->info.culoare;
//            nou->info.denumire = (char*)malloc(strlen(cap->info.denumire) + 1);
//            strcpy(nou->info.denumire, cap->info.denumire);
//            nou->next = capSimplu;
//            capSimplu = nou;
//        }
//        cap = cap->next;
//    }
//    return capSimplu;
//}
//
//void interschimbareElemente(NodDublu* cap, int poz1, int poz2) {
//    if (cap == NULL || poz1 == poz2) return;
//
//    NodDublu* p1 = cap, * p2 = cap;
//    for (int i = 0; i < poz1 && p1 != NULL; i++) p1 = p1->next;
//    for (int i = 0; i < poz2 && p2 != NULL; i++) p2 = p2->next;
//
//    if (p1 == NULL || p2 == NULL) return;
//
//    Mobila temp = p1->info;
//    p1->info = p2->info;
//    p2->info = temp;
//}
//
//void afisareLista(NodDublu* cap) {
//    afisareCrescator(cap);
//}
//
//int main() {
//    NodDublu* lista = NULL;
//    Mobila m1 = { 1, 101, "Scaun", 500.0, 'R' };
//    Mobila m2 = { 2, 102, "Masa", 1500.0, 'B' };
//    Mobila m3 = { 3, 103, "Dulap", 800.0, 'G' };
//
//    inserareSortata(&lista, m1);
//    inserareSortata(&lista, m2);
//    inserareSortata(&lista, m3);
//
//    printf("Lista crescator:\n");
//    afisareCrescator(lista);
//    printf("Lista descrescator:\n");
//    afisareDescrescator(lista);
//
//    stergeNodPozitie(&lista, 1);
//    printf("Lista dupa stergere:\n");
//    afisareLista(lista);
//
//    interschimbareElemente(lista, 0, 1);
//    printf("Lista dupa interschimbare:\n");
//    afisareLista(lista);
//
//    return 0;
//}
//
