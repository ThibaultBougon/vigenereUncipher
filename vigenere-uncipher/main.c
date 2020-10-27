#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "frequencyAnalysis.h"
#include "uncipher.h"

int main(int argc, char** argv) {
	FILE* fileIn, * fileOut;

	if ((fileIn = fopen("chal11.txt", "r")) == NULL) {
		fprintf(stderr,"fail open file in");
		return EXIT_FAILURE;
	}

	if ((fileOut = fopen("out.txt", "w")) == NULL) {
		fprintf(stderr, "fail open file out");
		return EXIT_FAILURE;	
	}

	int keySize = 0;
	printf("taille de la clef = ");
	scanf("%d", &keySize);

	int* shift;
	shift = initFreqAnalysis(fileIn, keySize);

	uncipherVigenere(fileIn, keySize, shift, fileOut);

	free(shift);
	fclose(fileIn);
	fclose(fileOut);

	return 0;
}
