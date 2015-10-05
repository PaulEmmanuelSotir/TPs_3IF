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
	if (heap == NULL)
		return;

	heap->allocated = ALLOC_STEP;
	heap->filled = 0;
	heap->array = (int*)malloc(sizeof(int)*ALLOC_STEP);
}

void ReallocIfFull(BinaryHeap* heap)
{
	if (heap == NULL)
		return;

	if (heap->filled >= heap->allocated)
	{
		heap->array = (int*)realloc(heap->array, heap->allocated + sizeof(int)*ALLOC_STEP);
		heap->allocated += ALLOC_STEP;
	}
}

void insert(BinaryHeap* heap, int value)
{
	if (heap == NULL)
		return;
	if (heap->array == NULL)
		return;

	ReallocIfFull(heap);

	heap->array[heap->filled] = value;

	int position_pére = (heap->filled - 1) / 2;
	int position_element_inséré = heap->filled;
	while (position_pére >= 0 && heap->array[position_pére] < heap->array[position_element_inséré])
	{
		int tampon = heap->array[position_pére];
		heap->array[position_pére] = heap->array[position_element_inséré];
		heap->array[position_element_inséré] = tampon;
		position_element_inséré = position_pére;
		position_pére = (position_pére - 1) / 2;
	}

	heap->filled++;
}

void Display(BinaryHeap* heap)
{
	if (heap == NULL)
		return;
	if (heap->array == NULL)
		return;

	unsigned int i;
	for (i = 0; i < heap->filled; i++)
		printf("%d\n\r", heap->array[i]);
}

void extract(BinaryHeap* heap)
{
	if (heap == NULL)
		return;
	if (heap->array == NULL || heap->filled == 0)
		return;

	if (heap->filled > 1)
	{
		// swap first and last value
		heap->array[heap->filled] = heap->array[heap->filled];

		// Remove last element from bnary heap
		heap->filled--;

		int i = 0;
		//while ()
		//{
		//	
		//}
	}
	else
		heap->filled--;
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
			Display(&heap);
		}
		else if (strcmp("extract", input) == 0)
		{
			extract(&heap);
			Display(&heap);
		}
		else
			printf("Invalid input");
	}
	return 0;
}