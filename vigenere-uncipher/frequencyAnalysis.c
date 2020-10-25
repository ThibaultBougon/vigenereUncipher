#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequencyAnalysis.h"

int* initFreqAnalysis(FILE* in, int keySize) {
	txtFile** txtParsed = NULL;
	int* shift = NULL;

	txtParsed = txtParser(in, keySize, txtParsed);
	if (txtParsed == NULL)
		fprintf(stderr, "error return txt parser");

	shift = freqAnalysis(keySize, txtParsed);

	for (int u = 0; u < keySize; ++u) {
		freeLi(txtParsed[u]);
	}
	
	return shift;
}


txtFile** txtParser(FILE* in, int keySize, txtFile** txtParsed) {
	txtParsed = malloc(keySize * sizeof(txtFile));
	if (!txtParsed)
		return NULL;

	for (int u = 0; u < keySize; ++u) {
		txtParsed[u] = NULL;
	}

	unsigned char buffer[BUFFER_SIZE + 1];
	size_t size;

	int buffU = 0;

	do {
		size = fread(buffer, 1, BUFFER_SIZE, in);
		buffer[size] = '\0';
		int a = 'a' - 'A';
		int u = buffU;

		for (int i = 0; i < size; ++i, ++u) {
			if (buffer[i] >= 'a' && buffer[i] <= 'z') {
				txtParsed[u % keySize] = pushBackList(txtParsed[u % keySize], buffer[i]);
			}
			else if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
				txtParsed[u % keySize] = pushBackList(txtParsed[u % keySize], (buffer[i] + a));
			}
			else {
				--u;
			}
		}

		buffU = u;
	} while (size == BUFFER_SIZE);

	return txtParsed;
}

int* freqAnalysis(int keySize, txtFile** txtParsed) {
	unsigned int** letFreq;
	letFreq = malloc(keySize * sizeof(unsigned int*));
	if (!letFreq)
		return NULL;
	for (int u = 0; u < keySize; ++u) {
		letFreq[u] = malloc(ALPHABET_LENGHT * sizeof(unsigned int));
		memset(letFreq[u], NULL, ALPHABET_LENGHT * sizeof(unsigned int));
	}

	for (int u = 0; u < keySize; ++u) {
		while (txtParsed[u]) {
			letFreq[u][(txtParsed[u]->x -97)] += 1;
			txtParsed[u] = txtParsed[u]->next;
		}
	}

	int* shift;
	shift = malloc(keySize * sizeof(int));
	if (!shift)
		return NULL;

	int actualValue = 0;
	int actualPosition = 0;

	for (int y = 0; y < keySize; ++y) {
		for (int x = 0; x < ALPHABET_LENGHT; ++x) {
			if (actualValue < letFreq[y][x]) {
				actualValue = letFreq[y][x];
				actualPosition = x;
			}
		}
		shift[y] = actualPosition -4;
		actualValue = 0;
	}

	return shift;// ToDo : free
}

