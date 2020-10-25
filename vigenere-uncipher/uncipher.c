#include <stdio.h>
#include <stdlib.h>
#include "uncipher.h"
#include "frequencyAnalysis.h"

void uncipherVigenere(FILE* in, int keySize, int* shift, FILE* out) {
	txtFile* txtUncipher;
	fseek(in, 0, SEEK_SET);
	txtUncipher = unshift(in, keySize, shift);
	printTxt(txtUncipher, keySize, out);
	freeLi(txtUncipher);
}

txtFile* unshift(FILE *in, int keySize, int *shift){

	txtFile* txtUncipher;
	txtUncipher = NULL;
	unsigned char buffer[BUFFER_SIZE + 1];
	size_t size;

	int buffU = 0;

	do {
		size = fread(buffer, 1, BUFFER_SIZE, in);
		buffer[size] = '\0';
		int u = buffU;

		for (int i = 0; i < size; ++i, ++u) {
			if ((buffer[i] >= 'a' && buffer[i] <= 'z') && (buffer[i] - shift[u%keySize]) >= 'a') {
				txtUncipher = pushBackList(txtUncipher, buffer[i]-shift[u % keySize]);
			}
			else if ((buffer[i] >= 'a' && buffer[i] <= 'z') && (buffer[i] - shift[u % keySize]) < 'a') {
				txtUncipher = pushBackList(txtUncipher, buffer[i] - shift[u % keySize] + ALPHABET_LENGHT);
			}
			else if (buffer[i] >= 'A' && buffer[i] <= 'Z' && (buffer[i] - shift[u % keySize]) >= 'A') {
				txtUncipher = pushBackList(txtUncipher, (buffer[i] - shift[u % keySize]));
			}
			else if (buffer[i] >= 'A' && buffer[i] <= 'Z' && (buffer[i] - shift[u % keySize]) < 'A') {
				txtUncipher = pushBackList(txtUncipher, (buffer[i] - shift[u % keySize]) + ALPHABET_LENGHT);
			}
			else {
				--u;
				txtUncipher = pushBackList(txtUncipher, buffer[i]);
			}
		}

		buffU = u;
	} while (size == BUFFER_SIZE);

	txtUncipher = pushBackList(txtUncipher, "\0");
}

void printTxt(txtFile* txtUncipher, int keySize, FILE *out) {
	while (txtUncipher)
	{
		fprintf(out, "%c", txtUncipher->x);
		txtUncipher = txtUncipher->next;
	}
}