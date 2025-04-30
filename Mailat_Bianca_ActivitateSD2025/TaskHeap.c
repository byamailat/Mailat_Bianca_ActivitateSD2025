#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct StructuraPacient {
	int id;
	int varsta;
	int gradUrgenta;
	char* nume;
};
typedef struct StructuraPacient Pacient;

struct Heap {
	Pacient* pacienti;
	int lungime;
	int nrPacienti;
};
typedef struct Heap Heap;

Pacient citirePacientDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Pacient p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	aux = strtok(NULL, sep);
	p.varsta = atoi(aux);

	aux = strtok(NULL, sep);
	p.gradUrgenta = atoi(aux);

	aux = strtok(NULL, sep);
	p.nume = malloc(strlen(aux) + 1);
	strcpy_s(p.nume, strlen(aux) + 1, aux);

	return p;
}

void afisarePacient(Pacient p) {
	printf("ID: %d\n", p.id);
	printf("Varsta: %d\n", p.varsta);
	printf("Grad urgenta: %d\n", p.gradUrgenta);
	printf("Nume: %s\n\n", p.nume);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrPacienti = 0;
	heap.pacienti = (Pacient*)malloc(sizeof(Pacient) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	if (pozitieNod >= 0 && pozitieNod < heap.nrPacienti) {
		int pozStanga = 2 * pozitieNod + 1;
		int pozDreapta = 2 * pozitieNod + 2;
		int pozMaxim = pozitieNod;

		if (pozStanga < heap.nrPacienti && heap.pacienti[pozMaxim].gradUrgenta < heap.pacienti[pozStanga].gradUrgenta) {
			pozMaxim = pozStanga;
		}
		if (pozDreapta < heap.nrPacienti && heap.pacienti[pozMaxim].gradUrgenta < heap.pacienti[pozDreapta].gradUrgenta) {
			pozMaxim = pozDreapta;
		}

		if (pozMaxim != pozitieNod) {
			Pacient aux = heap.pacienti[pozMaxim];
			heap.pacienti[pozMaxim] = heap.pacienti[pozitieNod];
			heap.pacienti[pozitieNod] = aux;

			if (pozMaxim < (heap.nrPacienti) / 2 - 1) {
				filtreazaHeap(heap, pozMaxim);
			}
		}
	}
}

Heap citireHeapDePacientiDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(20);
	FILE* file = fopen(numeFisier, "r");
	int index = 0;

	while (!feof(file)) {
		heap.pacienti[index] = citirePacientDinFisier(file);
		index++;
	}
	fclose(file);

	heap.nrPacienti = index;

	for (int i = (heap.nrPacienti - 1) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrPacienti; i++) {
		afisarePacient(heap.pacienti[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrPacienti; i < heap.lungime; i++) {
		afisarePacient(heap.pacienti[i]);
	}
}

Pacient extragePacient(Heap* heap) {
	Pacient aux = heap->pacienti[0];
	heap->pacienti[0] = heap->pacienti[heap->nrPacienti - 1];
	heap->pacienti[heap->nrPacienti - 1] = aux;
	heap->nrPacienti--;

	for (int i = (heap->nrPacienti - 1) / 2; i >= 0; i--) {
		filtreazaHeap(*heap, i);
	}
	return aux;
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->pacienti[i].nume);
	}
	free(heap->pacienti);
	heap->nrPacienti = 0;
	heap->lungime = 0;
	heap->pacienti = NULL;
}

int main() {
	Heap heap = citireHeapDePacientiDinFisier("pacienti.txt.txt");

	printf("Lista pacienti initiala:\n");
	afisareHeap(heap);

	printf("\nExtr 3 pacienti urgenti:\n");
	extragePacient(&heap);
	extragePacient(&heap);
	extragePacient(&heap);

	printf("\nPacienti ramasi in asteptare:\n");
	afiseazaHeapAscuns(heap);

	dezalocareHeap(&heap);
	return 0;
}
