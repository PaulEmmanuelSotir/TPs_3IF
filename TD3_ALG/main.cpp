#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_STEP 10

/*
 * La racine se situe à l'index 0
 * Soit un nœud à l'index i alors son fils gauche est à l'index 2i+1 et son fils droit à 2i+2
 * Soit un nœud à l'index i>0 alors son père est à l'index int((i-1)/2)
*/

typedef struct
{
	int allocated;
	int filled;
	int* array;
} BinaryHeap;

BinaryHeap* make_binaryHeap()
{
	BinaryHeap* newHeap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
	newHeap->allocated = ALLOC_STEP;
	newHeap->filled = 0;
	return newHeap;
}

void insert(BinaryHeap* heap, int value)
{

}

void extract(BinaryHeap* heap)
{

}

int main(int argc, const char* argv[])
{
	char input[30];
	BinaryHeap* heap = make_binaryHeap();

	while (1)
	{
		scanf("%s", input);

		if (strcmp("bye", input) == 0)
			break;
		else if (strcmp("insert", input) == 0)
		{
			int value = 0;
			scanf("%d", &value);
			insert(heap, value);
		}
		else if (strcmp("extract", input) == 0)
		{
			extract(heap);
		}
		else
			printf("Invalid input");
	}
	return 0;
}