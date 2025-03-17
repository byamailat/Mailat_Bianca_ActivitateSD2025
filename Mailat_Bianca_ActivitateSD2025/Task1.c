#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mobila {
    int id;
    int nrArticol;
    char* denumire;
    float pret;
    char culoare;
};

struct Mobila initializare(int idNou, int nrArticol, char* denumire, float pret, char culoare) {
    struct Mobila m;
    m.id = idNou;
    m.nrArticol = nrArticol;
    m.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
    strcpy_s(m.denumire, strlen(denumire) + 1, denumire);
    m.pret = pret;
    m.culoare = culoare;
    return m;
}

void afisare(struct Mobila m) {
    if (m.denumire != NULL) {
        printf("\nMobila cu id: %d, numar articol: %d, are denumirea: %s, pretul: %.2f si culoarea: %c\n",
            m.id, m.nrArticol, m.denumire, m.pret, m.culoare);
    }
}

void modifica_Atribut(struct Mobila* m, int nrElemente, float pretNou) {
    for (int i = 0; i < nrElemente; i++) {
        if (m[i].pret  >3000) {
            m[i].pret = pretNou; 
        }
    }
}

float calculeazaSumaPreturi(struct Mobila* m, int nrElemente) {
    float suma = 0;
    for (int i = 0; i < nrElemente; i++) {
        suma += m[i].pret;
    }
    return suma;
}

void dezalocare(struct Mobila* m, int nrElemente) {
    for (int i = 0; i < nrElemente; i++) {
        if (m[i].denumire) {
            free(m[i].denumire);
            m[i].denumire = NULL;
        }
    }
}

int main() {
    struct Mobila m[3];
    m[0] = initializare(1, 22, "mobila", 6000, 'A');
    m[1] = initializare(2, 33, "Masa", 2500, 'B');
    m[2] = initializare(3, 44, "Dulap", 500, 'G');

    printf("\nInainte de modificare:\n");
    for (int i = 0; i < 3; i++) {
        afisare(m[i]);
    }

    modifica_Atribut(m, 3, 4000);

    printf("\nDupa modificare:\n");
    for (int i = 0; i < 3; i++) {
        afisare(m[i]);
    }
    float suma = calculeazaSumaPreturi(m, 3);
    printf("\nSuma totala a preturilor este: %.2f\n", suma);

    dezalocare(m, 3);

    return 0;
}
