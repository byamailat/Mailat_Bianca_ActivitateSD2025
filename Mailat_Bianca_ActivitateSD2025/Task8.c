#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Cladire {
    int id;
    int anConstructie;
    char* adresa; 
    struct Cladire* next;
} Cladire;

Cladire* tabela[TABLE_SIZE];
int hash(int an) {
    return an % TABLE_SIZE;
}
void inserareCladire(int id, int an, const char* adresa) {
    int index = hash(an);
    Cladire* noua = (Cladire*)malloc(sizeof(Cladire));
    noua->id = id;
    noua->anConstructie = an;
    noua->adresa = _strdup(adresa);
    noua->next = tabela[index];
    tabela[index] = noua;
}
void afisareClusterePeAn(int an) {
    int index = hash(an);
    Cladire* temp = tabela[index];
    while (temp) {
        if (temp->anConstructie == an)
            printf("ID: %d, An: %d, Adresa: %s\n", temp->id, temp->anConstructie, temp->adresa);
        temp = temp->next;
    }
}
void stergereCladireIDAn(int id, int an) {
    int index = hash(an);
    Cladire* temp = tabela[index];
    Cladire* anterior = NULL;

    while (temp) {
        if (temp->id == id && temp->anConstructie == an) {
            if (anterior)
                anterior->next = temp->next;
            else
                tabela[index] = temp->next;

            free(temp->adresa);
            free(temp);
            return;
        }
        anterior = temp;
        temp = temp->next;
    }
}

void stergereCladireID(int id) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Cladire* temp = tabela[i];
        Cladire* anterior = NULL;
        while (temp) {
            if (temp->id == id) {
                if (anterior)
                    anterior->next = temp->next;
                else
                    tabela[i] = temp->next;

                free(temp->adresa);
                free(temp);
                return;
            }
            anterior = temp;
            temp = temp->next;
        }
    }
}
Cladire** vectorCladiriPeAn(int an, int* dimensiune) {
    int count = 0;
    int index = hash(an);
    Cladire* temp = tabela[index];

    
    while (temp) {
        if (temp->anConstructie == an)
            count++;
        temp = temp->next;
    }

    Cladire** vector = malloc(count * sizeof(Cladire*));
    *dimensiune = count;
    temp = tabela[index];
    int i = 0;

    while (temp) {
        if (temp->anConstructie == an) {
            vector[i] = malloc(sizeof(Cladire));
            vector[i]->id = temp->id;
            vector[i]->anConstructie = temp->anConstructie;
            vector[i]->adresa = _strdup(temp->adresa);
            vector[i]->next = NULL;
            i++;
        }
        temp = temp->next;
    }

    return vector;
}

void modificaAnConstructie(int id, int vechiAn, int nouAn) {
    int indexVechi = hash(vechiAn);
    Cladire* temp = tabela[indexVechi];
    Cladire* anterior = NULL;

    while (temp) {
        if (temp->id == id && temp->anConstructie == vechiAn) {
           
            if (anterior)
                anterior->next = temp->next;
            else
                tabela[indexVechi] = temp->next;

          
            temp->anConstructie = nouAn;
            int indexNou = hash(nouAn);
            temp->next = tabela[indexNou];
            tabela[indexNou] = temp;
            return;
        }
        anterior = temp;
        temp = temp->next;
    }
}
int main() {
    for (int i = 0; i < TABLE_SIZE; i++)
        tabela[i] = NULL;

    inserareCladire(101, 1977, "Str. Victoriei 10");
    inserareCladire(102, 1977, "Bd. Unirii 23");
    inserareCladire(103, 1990, "Str. Dorobanti 5");
    inserareCladire(104, 2000, "Str. Tineretului 11");

    printf("Cladirile din anul 1977:\n");
    afisareClusterePeAn(1977);

    int nr;
    Cladire** vector = vectorCladiriPeAn(1977, &nr);
    printf("\nVector copiat (deep copy):\n");
    for (int i = 0; i < nr; i++) {
        printf("ID: %d, An: %d, Adresa: %s\n", vector[i]->id, vector[i]->anConstructie, vector[i]->adresa);
        free(vector[i]->adresa);
        free(vector[i]);
    }
    free(vector);

    printf("\nModificare an pentru ID 102 din 1977 în 1985...\n");
    modificaAnConstructie(102, 1977, 1985);
    printf("Cladirile din 1977:\n");
    afisareClusterePeAn(1977);
    printf("Cladirile din 1985:\n");
    afisareClusterePeAn(1985);

    printf("\nStergere cladire ID 101, an 1977...\n");
    stergereCladireIDAn(101, 1977);
    afisareClusterePeAn(1977);

    printf("\nStergere cladire ID 103 (nu stim anul)...\n");
    stergereCladireID(103);
    printf("Cladirile din 1990:\n");
    afisareClusterePeAn(1990);

    return 0;
}
