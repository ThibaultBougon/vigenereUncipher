#pragma once
#include "list.h"

txtFile* unshift(FILE* in, int keySize, int* shift);
void printTxt(txtFile* txtUncipher, int keySize, FILE* out);
void uncipherVigenere(FILE* in, int keySize, int* shift, FILE* out);