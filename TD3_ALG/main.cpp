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
		heap->array = (int*)realloc(heap->array, sizeof(int) * (ALLOC_STEP + heap->allocated));
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
		printf("%d\r\n", heap->array[i]);
}

void swapValues(int* array, unsigned int idx1, unsigned int* idx2)
{
	unsigned int tmp = array[idx1];
	array[idx1] = array[*idx2];
	array[*idx2] = tmp;
	*idx2 = idx1;
}

int extract(BinaryHeap* heap, int* max)
{
	if (heap->filled <= 0 || max == NULL || heap == NULL)
		return 0;
	
	*max = heap->array[0];

	if (heap->filled > 1)
	{
		// swap first and last value
		heap->array[0] = heap->array[heap->filled-1];

		// Remove last element from bnary heap
		heap->filled--;
		unsigned int max_pos = heap->filled - 1;

		unsigned int pos_element = 0;
		while (1)
		{
			unsigned int pos_fils1 = pos_element * 2 + 1;
			unsigned int pos_fils2 = pos_element * 2 + 2;

			if(pos_fils2 > max_pos && pos_fils1 <= max_pos) {
				if (heap->array[pos_fils1] > heap->array[pos_element])
					swapValues(heap->array, pos_fils1, &pos_element);
				else
					break;
			}
			else if(pos_fils2 <= max_pos && pos_fils1 <= max_pos)
			{
				if (heap->array[pos_fils1] > heap->array[pos_element] || heap->array[pos_fils2] > heap->array[pos_element])
				{
					if (heap->array[pos_fils1] > heap->array[pos_fils2])
						swapValues(heap->array, pos_fils1, &pos_element);
					else
						swapValues(heap->array, pos_fils2, &pos_element);
				}
				else
					break;
			}
			else
				break;
		}
	}
	else
		heap->filled--;

	return 1;
}

void dispose(BinaryHeap* heap)
{
	free(heap->array);
	heap->array = NULL;
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
			int max = 0;
			if(extract(&heap, &max))
				printf("%d\r\n", max);
		}
		else
			printf("Invalid input");
	}

	dispose(&heap);

	return 0;
}