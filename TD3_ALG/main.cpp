#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_STEP 5

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

void init(BinaryHeap* heap)
{
	heap->allocated = ALLOC_STEP;
	heap->filled = 0;
	heap->array = (int*)malloc(sizeof(int)*ALLOC_STEP);
}

void ReallocIfFull(BinaryHeap* heap)
{
	if (heap->filled >= heap->allocated)
	{
		heap->array = (int*)realloc(heap->array, heap->allocated + sizeof(int)*ALLOC_STEP);
		heap->allocated += ALLOC_STEP;
	}
}

void insert(BinaryHeap* heap, int value)
{
	ReallocIfFull(heap);

}

void extract(BinaryHeap* heap)
{

}

int main(int argc, const char* argv[])
{
	char input[30];
	BinaryHeap heap;
	init(&heap);

	while (1)
	{
		scanf("%s", input);

		if (strcmp("bye", input) == 0)
			break;
		else if (strcmp("insert", input) == 0)
		{
			int value = 0;
			scanf("%d", &value);
			insert(&heap, value);
		}
		else if (strcmp("extract", input) == 0)
		{
			extract(&heap);
		}
		else
			printf("Invalid input");
	}
	return 0;
}