#include<stdio.h>
#include<malloc.h>
#include <string.h>

struct Student {
	int id;
	int varsta;
	char* nume;
	float medie ;
	char gen;
};
struct Student initializare(int idNou, int varstaNoua, char* numeNou, float medieNoua, char genNou) {
	struct Student s;
	s.id = idNou;
	s.varsta = varstaNoua;
	s.nume = malloc(sizeof(char) * (strlen(numeNou) + 1));
	strcpy_s(s.nume, strlen(numeNou) + 1, numeNou);
	s.medie = medieNoua;
	s.gen = genNou;


	return s;
}

void afisare(struct Student s){
	//afisarea tuturor atributelor.
	if (s.nume != NULL) {
		printf("Id: %d\n Varsta: %d \n Nume: %s\n Medie:%.2f\n Gen: %c\n\n", s.id, s.varsta, s.nume, s.medie, s.gen);
	}
	}

void afisareVector(struct Student* vectorStudenti, int nrStudenti) {
	for (int i = 0; i < nrStudenti; i++) {
		afisare(vectorStudenti[i]);
	}
}

struct Student* copiazaPrimeleNElemente(struct Student* vectorStudenti, int nrStudenti, int nrStudentiCopiati) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Student *vectorNou=NULL;
	vectorNou = (struct Student*)malloc(sizeof(struct Student) * nrStudentiCopiati);
	for (int i = 0; i < nrStudentiCopiati; i++) {
		vectorNou[i] = vectorStudenti[i];
		vectorNou[i].nume = (char*)malloc(strlen(vectorStudenti[i].nume) + 1);
		strcpy_s(vectorNou[i].nume, strlen(vectorStudenti[i].nume) + 1, vectorStudenti[i].nume);
	}
	return vectorNou;
}

void dezalocare(struct Student** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < (*nrElemente); i++) {
		if ((*vector)[i].nume != NULL) {
			free((*vector)[i].nume);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;

}

void copiazaVarsta21(struct Student* vector, char nrElemente, int varstaMinima, struct Student** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	

	//studentii cu varsta=21
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].varsta == varstaMinima) {
			(*dimensiune)++;
		}
	}
	if ((*vectorNou) != NULL) {
		free(*vectorNou);
	}
	*vectorNou = (struct Student*)malloc(sizeof(struct Student) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].varsta == varstaMinima) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s((*vectorNou)[k].nume, strlen(vector[i].nume) + 1, vector[i].nume);
			k++;
		}
	}
	

}

struct Student* copiazaStudentiMasculini(struct Student* vector, int nrElemente,  int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].gen == 'M') {
			(*dimensiune)++;
		}

	}

	if ((*dimensiune) == 0) {
		return NULL; }

	struct Student* vectorNou = (struct Student*)malloc(sizeof(struct Student) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].gen == 'M') {
			vectorNou[k] = vector[i];
			vectorNou[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s(vectorNou[k].nume, strlen(vector[i].nume) + 1, vector[i].nume);
			k++;
		}
	}
	return vectorNou;
}


int main() {
	struct Student* studenti = NULL;
	int nrStudenti = 5;
	studenti = (struct Student*)malloc(sizeof(struct Student) * nrStudenti);
	studenti[0] = initializare(1, 20, "Bianca", 9, 'F');
	studenti[1] = initializare(2, 21, "Alina", 10, 'F');
	studenti[2] = initializare(3, 22, "Cristina", 9.5, 'F');
	studenti[3] = initializare(4, 21, "Alex", 10, 'M');
	studenti[4] = initializare(5, 21, "Alin", 9.75, 'M');

	afisareVector(studenti, nrStudenti);

	struct Student* primiiStudenti = NULL;
	int nrPrimiiStudenti = 2;
	primiiStudenti = copiazaPrimeleNElemente(studenti, nrStudenti, nrPrimiiStudenti);
	printf("\n\n Primele Telefoane \n:");
	afisareVector(primiiStudenti, nrPrimiiStudenti);

	dezalocare(&primiiStudenti, &nrPrimiiStudenti);
	printf("\n\n Primele Telefoane verif: \n");
	afisareVector(primiiStudenti, nrPrimiiStudenti);

	//copiaza stud cu varsta 21
	struct Student* studentiVarsta21 = NULL;
	int nrStudenti21 = 0;
	copiazaVarsta21(studenti, nrStudenti, 21,&studentiVarsta21,&nrStudenti21);
	printf("\n\nStudenti cu varsta 21:\n");
	afisareVector(studentiVarsta21, nrStudenti21);
	dezalocare(&studentiVarsta21, &nrStudenti21);

	afisareVector(studenti, nrStudenti);
	
	//copiaza gen masculin
	int nrStudentiMasculini = 0;
	struct Student* studentiMasculini = copiazaStudentiMasculini(studenti, nrStudenti, &nrStudentiMasculini);

	if (studentiMasculini != NULL) {
		printf("\n\nStudenti de gen masculin:\n");
		afisareVector(studentiMasculini, nrStudentiMasculini);
		free(studentiMasculini);
	}
	else {
		printf("\n\nNu exista studenti de gen masculin.\n");
	}

	free(studenti);
	return 0;
}