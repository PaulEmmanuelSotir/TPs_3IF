#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define TESTING
#define ENDL "\r\n"

//typedef enum { false, true } bool;

typedef struct element
{
	int value;
	struct element* previous;
	struct element* next;
} element;

element* make_list()
{
	element* sentinel = (element*)malloc(sizeof(element));
	sentinel->next = sentinel;
	sentinel->previous = sentinel;
	return sentinel;
}

element* insert(element* list, int value)
{
	element* new_element = (element*)malloc(sizeof(element));
	if (new_element == NULL || list == NULL)
		return NULL;
	new_element->value = value;

	element* it = list->next;

	// First element
	if (it == list)
	{
		list->next = new_element;
		list->previous = new_element;
		new_element->previous = list;
		new_element->next = list;
		return new_element;
	}

	while (list != it)
	{
		if (it->value >= value)
		{
			// Insert
			it->previous->next = new_element;
			new_element->next = it;
			new_element->previous = it->previous;
			it->previous = new_element;
			return new_element;
		}
		it = it->next;
	}

	// Last element
	list->previous->next = new_element;
	new_element->next = list;
	new_element->previous = list->previous;
	list->previous = new_element;
	return new_element;
}

element* make_list2(int* values, size_t size)
{
	if (values == NULL || size == 0)
		return make_list();

	element* sentinel = make_list();
	
	unsigned int i;
	for (i = 0; i < size; i++)
		insert(sentinel, values[i]);

	return sentinel;
}

void remove(element* list, int value)
{
	if (list == NULL)
		return;

	element* it = list->next;

	// Empty list
	if (it == list)
		return;

	while (list != it)
	{
		if (it->value == value)
		{
			// Remove element
			it->previous->next = it->next;
			it->next->previous = it->previous;
			free(it);
			return;
		}
		it = it->next;
	}

	return;
}

void display(element* list)//, bool rubbishDisplayMode)
{
	if (list != NULL)
	{
	//	if (!rubbishDisplayMode)
	//		printf("[ ");
		element* it = list->next;
		while (it != list)
		{
	//		if(!rubbishDisplayMode)
	//			printf(it->next == list ? "%d" : "%d, ", it->value);
	//		else
				printf("%d\r\n", it->value);
			it = it->next;
		}
	//	if (!rubbishDisplayMode)
	//		printf(" ]");
	}
	else
		printf("NULL");
}

void dispose(element* list)
{
	if (list == NULL)
		return;

	// Empty list
	if (list->next == list) {
		free(list);
		return;
	}

	list->previous->next = NULL;
	element* it = list->next;

	while (it->next != NULL)
	{
		free(it->previous);
		it->previous = NULL;
		it = it->next;
	}

	if (it->previous != it)
		free(it->previous);
	free(it);
}

int main(int argc, const char* argv[])
{
#ifdef TESTING
	int initialValues[] = { 10, 30, -20, 4 };
	element* list = make_list(initialValues, 4);

	printf("List = ");
	display(list);

	insert(list, 11);
	insert(list, -15);

	printf("\r\nList = ");
	display(list);

	remove(list, 10);
	remove(list, 8);

	printf("\r\nList = ");
	display(list);

	dispose(list);
#else
	char input[30];
	element* list = make_list();

	while (1)
	{
		scanf("%s", input);

		if (strcmp("print", input) == 0)
		{
			display(list);
			printf(ENDL);
		}
		else if (strcmp("bye", input) == 0)
			break;
		else if (strcmp("insert", input) == 0)
		{
			int value = 0;
			scanf("%d", &value);
			insert(list, value);
		}
		else if (strcmp("remove", input) == 0)
		{
			int value = 0;
			scanf("%d", &value);
			remove(list, value);
		}
		else
			printf("Invalid input");
	}
#endif

	return 0;
}