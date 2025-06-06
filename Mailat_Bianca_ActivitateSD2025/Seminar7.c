//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Heap {
//	Masina* masini;
//	int lungime;
//	int nrMasini;
//
//};
//typedef struct Heap Heap;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrMasini = 0;
//	heap.masini = (Masina*)malloc(sizeof(Masina) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
//	//in functie de tipul de heap (maxim avem noi aici)
//
//	if (pozitieNod >= 0 && pozitieNod < heap.nrMasini) {
//		int pozStanga = 2 * pozitieNod + 1;
//		int pozDreapta = 2 * pozitieNod + 2;
//		int pozMaxim = pozitieNod;
//		if (pozStanga < heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[pozStanga].id) {
//			pozMaxim = pozStanga;
//		}
//
//		if (pozDreapta < heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[pozDreapta].id) {
//			pozMaxim = pozDreapta;
//		}
//		if (pozMaxim != pozitieNod) {
//			Masina aux = heap.masini[pozMaxim];
//			heap.masini[pozMaxim] = heap.masini[pozitieNod];
//			heap.masini[pozitieNod] = aux;
//
//			if (pozMaxim < (heap.nrMasini) / 2 - 1)
//			{
//				filtreazaHeap(heap, pozMaxim);
//
//			}
//
//		}
//
//	}
//
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	//citim toate masinile din fisier si le stocam intr-un heap 
//	// pe care trebuie sa il filtram astfel incat sa respecte 
//	// principiul de MAX-HEAP sau MIN-HEAP dupa un anumit criteriu
//	// sunt citite toate elementele si abia apoi este filtrat vectorul
//
//	Heap heap = initializareHeap(10);
//	FILE* file = fopen(numeFisier, "r");
//	int index = 0;
//
//	while (!feof(file))
//	{
//		heap.masini[index] = citireMasinaDinFisier(file);
//		index++;
//
//	}
//	heap.nrMasini = index;
//	for (int i = (heap.nrMasini - 1) / 2; i >= 0; i--) { //for pt parinti
//		filtreazaHeap(heap, i);
//		return heap;
//	}
//	
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini; i++)
//	{
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	for (int i = heap.nrMasini; i < heap.lungime; i++)
//	{
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) {
//	//extrage si returneaza masina de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
//	Masina aux;
//	aux = heap->masini[0];
//	heap->masini[0] = heap->masini[heap->nrMasini - 1];
//	heap->masini[heap->nrMasini - 1] = aux;
//	heap->nrMasini--; //scadem ult ca sa nu mai fie vizibil
//	for (int i = (heap->nrMasini - 1) / 2; i >= 0; i--) {
//		filtreazaHeap(*heap, i);
//	}
//	return aux;
//}
//
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++)
//	{
//		free(heap->masini[i].model);
//		free(heap->masini[i].numeSofer);
//	}
//	free(heap->masini);
//	heap->nrMasini = 0;
//	heap->lungime = 0;
//	heap->masini = NULL;
//}
//
//int main() {
//	Heap heap = citireHeapDeMasiniDinFisier("masini.txt.txt");
//
//	afisareHeap(heap);
//
//
//	extrageMasina(&heap);
//	extrageMasina(&heap);
//	extrageMasina(&heap);
//	extrageMasina(&heap);
//	extrageMasina(&heap);
//	extrageMasina(&heap);
//
//	printf("---------------------------\n\n");
//	afiseazaHeapAscuns(heap);
//	dezalocareHeap(&heap);
//	return 0;
//}