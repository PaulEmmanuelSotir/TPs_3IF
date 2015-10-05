#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_STEP 5

/*
 * La racine se situe � l'index 0
 * Soit un n�ud � l'index i alors son fils gauche est � l'index 2i+1 et son fils droit � 2i+2
 * Soit un n�ud � l'index i>0 alors son p�re est � l'index int((i-1)/2)
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

	int position_p�re = (heap->filled - 1) / 2;
	int position_element_ins�r� = heap->filled;
	while (position_p�re >= 0 && heap->array[position_p�re] < heap->array[position_element_ins�r�])
	{
		int tampon = heap->array[position_p�re];
		heap->array[position_p�re] = heap->array[position_element_ins�r�];
		heap->array[position_element_ins�r�] = tampon;
		position_element_ins�r� = position_p�re;
		position_p�re = (position_p�re - 1) / 2;
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