#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_STEP 5
#define _CRT_SECURE_NO_WARNINGS
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

	int position_pere = (heap->filled - 1) / 2;
	int position_element_insere = heap->filled;
	while (position_pere >= 0 && heap->array[position_pere] < heap->array[position_element_insere])
	{
		int tampon = heap->array[position_pere];
		heap->array[position_pere] = heap->array[position_element_insere];
		heap->array[position_element_insere] = tampon;
		position_element_insere = position_pere;
		position_pere = (position_pere - 1) / 2;
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

void swapValues(int* array, unsigned int idx1, unsigned int& idx2)
{
	unsigned int tmp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = tmp;
	idx2 = idx1;
}

int extract(BinaryHeap* heap)
{
	if (heap == NULL)
		return;
	if (heap->array == NULL || heap->filled == 0)
		return;

	int max_value;
	max_value = heap->array[0];

	if (heap->filled > 1)
	{
		// swap first and last value
		heap->array[0] = heap->array[heap->filled];

		// Remove last element from bnary heap
		heap->filled--;

		unsigned int pos_element = 0;
		while (1)
		{
			unsigned int pos_fils1 = pos_element * 2 + 1;
			unsigned int pos_fils2 = pos_element * 2 + 2;

			if(pos_fils2 > heap->filled && pos_fils1 <= heap->filled)
				if (heap->array[pos_fils1] > heap->array[pos_element]) {
					swapValues(heap->array, pos_fils1, pos_element);
				}
			else if(pos_fils2 <= heap->filled && pos_fils1 <= heap->filled)
			{
				if (heap->array[pos_fils1] > heap->array[pos_element] || heap->array[pos_fils2] > heap->array[pos_element])
				{
					if (heap->array[pos_fils1] > heap->array[pos_fils2])
						swapValues(heap->array, pos_fils1, pos_element);
					else
						swapValues(heap->array, pos_fils2, pos_element);
				}
				else
					break;
			}
			else break;
		}
	}
	else
		heap->filled--;

	return max_value;
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