#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct txtFile
{
	char x;
	struct txtFile *next;
}txtFile;

txtFile* pushBackList(txtFile* li, char x);
void freeLi(txtFile* li);