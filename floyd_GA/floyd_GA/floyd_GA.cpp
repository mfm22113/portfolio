//	This is a program to solve Floyd problem by GA (Genetic Algorithm).
//	Each individual has 0 or 1 in their loci. 0 represents the locus is in group A. 1 represents the locus is in group B.
//	The default conditions are below.
//	
//	100 generations, 100 individuals, and 50 digits.
//	Tournament selection (pick up 3 individuals, compare and the best individual is chosen as parent) 
//	and elite strategy (save 1 best individual) are used.
//	Mutation rate is 0.05.
// 
//	As default, it takes about 20 seconds to run.
//	Once you run this code, a console pops out and shows all individuals, their parents, crossover_point, score(differences), number of mutation and elapsed time.
//	Besides, "floyd_result.csv" is created in "floyd_GA". You can easily draw best-result-graph by using this file with excel.
//	Note that the "floyd_result.csv" is overwritten everytime. If you save a specific result, you have to change the file name.



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define D_GENERATION_NUM (100)							//number of generation, this should be >= 1.
#define D_INDIVIDUAL_NUM (100)							//number of individual,	this should be >= 3 because of the tournament selection.
#define D_DIGIT_NUM (50)								//number of digit, this should be >= 2 because this program needs groupA and B.

//variables
int array[D_INDIVIDUAL_NUM][D_DIGIT_NUM] = { 0 };
int new_array[D_INDIVIDUAL_NUM][D_DIGIT_NUM] = { 0 };
int fathers[D_INDIVIDUAL_NUM - 1] = { 0 };
int mothers[D_INDIVIDUAL_NUM - 1] = { 0 };
int crossover[D_INDIVIDUAL_NUM - 1] = { 0 };
int elite[D_DIGIT_NUM] = { 0 };
double difference[D_INDIVIDUAL_NUM] = { 0 };
double best_difference = 100;
int father = -1;
int mother = -1;
int tournamentA = -1;
int tournamentB = -1;
int tournamentC = -1;
int crossover_point = -1;
int mutation_num = 0;

//functions
void INITIALIZE() {
	//	Initializing. This will randomly put 0 or 1 in all individual's loci.
	for (int i = 0; i < D_INDIVIDUAL_NUM; i++) {
		for (int k = 0; k < D_DIGIT_NUM; k++) {
			array[i][k] = rand() % 2;
		}
	}
}

void CALCULATE_DIFFERENCE() {
	//	Calculate difference between group A and B. Save the best one as "elite" at the same time.
	best_difference = 100;
	for (int i = 0; i < D_INDIVIDUAL_NUM; i++) {
		double sumA = 0;
		double sumB = 0;
		for (int j = 0; j < D_DIGIT_NUM; j++) {
			if (array[i][j] == 0) {
				sumA = sumA + (sqrt(j + 1));
			}
			else if (array[i][j] == 1) {
				sumB = sumB + (sqrt(j + 1));
			}
			else {
				printf("something's wrong1");
			}
		}
		if (sumA <= sumB) {
			difference[i] = sumB - sumA;
		}
		else if (sumA > sumB) {
			difference[i] = sumA - sumB;
		}
		else {
			printf("something's wrong2");
		}
		if (best_difference > difference[i]) {
			best_difference = difference[i];
			for (int k = 0; k < D_DIGIT_NUM; k++) {
				elite[k] = array[i][k];
			}
		}
	}
}

void INITIAL_PRINT() {
	//	Print the initial generation to console.
	printf("INITIAL GENERATION\n");
	for (int i = 0; i < D_INDIVIDUAL_NUM; i++) {
		printf("%d) ", i);
		for (int k = 0; k < D_DIGIT_NUM; k++) {
			printf("%d", array[i][k]);
		}
		printf("     %f", difference[i]);
		printf("\n");
	}
	printf("\n");
}

void FILE_WRITE() {
	//	Create "floyd_result.csv" and write.
	FILE* fp = fopen("floyd_result.csv", "w");
	if (fp == NULL) {
		perror("couldn't open the file\n");
	}
	if (fp != 0) {
		fprintf(fp, "%lf,", best_difference);
		fclose(fp);
	}
}

void TOURNAMENT_SELECT(int num) {
	//	Pick up 3 individuals, the best individual is chosen as parent.
	//	Repeat 2 times to pick up father and mother.
	for (int i = 0; i < 2; i++) {
		do {
			tournamentA = rand() % D_INDIVIDUAL_NUM;
			tournamentB = rand() % D_INDIVIDUAL_NUM;
			tournamentC = rand() % D_INDIVIDUAL_NUM;
		} while (tournamentA == tournamentB || tournamentB == tournamentC || tournamentC == tournamentA);

		if (difference[tournamentA] <= difference[tournamentB] && difference[tournamentA] <= difference[tournamentC]) {
			if (i == 0) {
				fathers[num] = tournamentA;
				father = tournamentA;
			}
			else if (i == 1) {
				mothers[num] = tournamentA;
				mother = tournamentA;
			}
			else {
				printf("something's wrong3");
			}
		}
		else if (difference[tournamentB] <= difference[tournamentA] && difference[tournamentB] <= difference[tournamentC]) {
			if (i == 0) {
				fathers[num] = tournamentB;
				father = tournamentB;
			}
			else if (i == 1) {
				mothers[num] = tournamentB;
				mother = tournamentB;
			}
			else {
				printf("something's wrong4");
			}
		}
		else if (difference[tournamentC] <= difference[tournamentA] && difference[tournamentC] <= difference[tournamentB]) {
			if (i == 0) {
				fathers[num] = tournamentC;
				father = tournamentC;
			}
			else if (i == 1) {
				mothers[num] = tournamentC;
				mother = tournamentC;
			}
			else {
				printf("something's wrong5");
			}
		}
	}
}

void CROSSOVER(int num) {
	//	Randomly decide where is the crossover_point, then create "new_array"s with crossover.
	crossover_point = rand() % (D_DIGIT_NUM - 1);
	crossover[num] = crossover_point;
	for (int i = 0; i < D_DIGIT_NUM; i++) {
		if (i <= crossover_point) {
			new_array[num][i] = array[father][i];
		}
		else if (i > crossover_point) {
			new_array[num][i] = array[mother][i];
		}
		else {
			printf("something's wrong6");
		}
	}
}

void MUTATION() {
	//	If mutation happens, 0 will be 1, and 1 will be 0.
	//	Mutation_rate will decide the probability of mutation.
	double mutation_rate = 0.05;
	double rand_num = 0;
	mutation_num = 0;
	for (int i = 0; i < D_INDIVIDUAL_NUM-1; i++) {
		for (int k = 0; k < D_DIGIT_NUM; k++) {
			rand_num = rand() / (double)RAND_MAX;
			if (rand_num <= mutation_rate) {
				mutation_num++;
				if (new_array[i][k] == 0) {
					new_array[i][k] = 1;
				}
				else if (new_array[i][k] == 1) {
					new_array[i][k] = 0;
				}
				else {
					printf("something's wrong7");
				}
			}
			else {
				new_array[i][k] = new_array[i][k];
			}
		}
	}
}

void ADD_ELITE() {
	//	Elite is added to the "new_array".
	for (int i = 0; i < D_DIGIT_NUM; i++) {
		new_array[D_INDIVIDUAL_NUM - 1][i] = elite[i];
	}
}

void REPLACE_ARRAY() {
	//	Replace "array" with "new_array".
	for (int i = 0; i < D_INDIVIDUAL_NUM; i++) {
		for (int k = 0; k < D_DIGIT_NUM; k++) {
			array[i][k] = new_array[i][k];
		}
	}
}

void NORMAL_PRINT() {
	//	Print the result to console.
	for (int i = 0; i < D_INDIVIDUAL_NUM; i++) {
		if (i == D_INDIVIDUAL_NUM - 1) {
			printf("%d)  elite  ", i);
		}
		else {
			printf("%d) (%d,%d) %d ", i, fathers[i], mothers[i], crossover[i]);
		}
		for (int k = 0; k < D_DIGIT_NUM; k++) {
			printf("%d", array[i][k]);
		}
		printf("     %f", difference[i]);
		printf("\n");
	}
}

void FILE_ADD() {
	//	Open the "floyd_result.csv" and add "best_difference".
	FILE* fp = fopen("floyd_result.csv", "a");
	if (fp == NULL) {
		perror("couldn't open the file\n");
	}
	if (fp != 0) {
		fprintf(fp, "%lf,", best_difference);
		fclose(fp);
	}
}

int main() {
	srand((unsigned int)time(NULL));
	clock_t start = clock();

	INITIALIZE();
	CALCULATE_DIFFERENCE();
	INITIAL_PRINT();
	FILE_WRITE();

	for (int gen = 0; gen < D_GENERATION_NUM; gen++) {
		printf("GENERATION%d", gen + 1);
		printf("\n");
		for (int i = 0; i < D_INDIVIDUAL_NUM - 1; i++) {
			TOURNAMENT_SELECT(i);
			CROSSOVER(i);
		}
		MUTATION();
		ADD_ELITE();
		REPLACE_ARRAY();
		CALCULATE_DIFFERENCE();
		NORMAL_PRINT();
		FILE_ADD();
		printf("\n");
		printf("number of mutation in this generation: %dtime(s)\n\n", mutation_num);
	}
	
	clock_t end = clock();
	printf("elapsed time = %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	return 0;
}

