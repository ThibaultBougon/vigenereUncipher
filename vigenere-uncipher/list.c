#include <stdio.h>
#include <stdlib.h>
#include "list.h"

txtFile* pushBackList(txtFile* li, char x)
{
	txtFile *element;

	element = malloc(sizeof(*element));

	if (!element)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		return NULL;
	}

	element->x = x;
	element->next = NULL;

	if (!li)
		return element;

	txtFile *buff;
	buff = li;

	while (buff->next != NULL)
		buff = buff->next;

	buff->next = element;

	return li;
}

void freeLi(txtFile* li) {
	if (li == NULL)
		return;
	if (li->next ==  NULL)
		return;
	freeLi(li->next);
	free(li->next);
}