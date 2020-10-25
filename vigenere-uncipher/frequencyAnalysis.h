#pragma once
#include "list.h"

#define BUFFER_SIZE 1024
#define ALPHABET_LENGHT 26

int* initFreqAnalysis(FILE* in, int keySize);
txtFile** txtParser(FILE* in, int keySize, txtFile** txtParsed);
int* freqAnalysis(int keySize, txtFile** txtParsed);