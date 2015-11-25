#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "hash_table.h"

static unsigned int hash(char* chaine, unsigned int m);
static unsigned int shift_rotate(unsigned int val, unsigned int n);
static unsigned int find_index_of(hash_table* table, char* key, unsigned int h);

void init_hash_table(hash_table* table, unsigned int repetition, unsigned int m)
{
	if (table != NULL)
	{
		table->m = m;
		table->array_size = repetition*m;
		table->array_step = repetition;
		table->used_count = 0;
		table->deleted_count = 0;

		table->array = (cell*)malloc(table->array_size*sizeof(cell));

		unsigned int i;
		for (i = 0; i < table->array_size; ++i)
		{
			cell* c = &table->array[i];
			c->state = empty;
			c->key = NULL;
			c->value = NULL;
		}
	}
}

void destr_hash_table(hash_table* table)
{
	if (table != NULL)
	{
		// Free all allocated strings
		unsigned int i;
		for (i = 0; i < table->array_size; ++i)
		{
			cell* c = &table->array[i];
			if (c != NULL)
			{
				if(c->key != NULL)
					free(c->key);
				if (c->value != NULL)
					free(c->value);
			}
		}

		// Free table of cells
		free(table->array);
		table->array = NULL;

		table->array_size = 0;
		table->used_count = 0;
		table->deleted_count = 0;
	}
}

void show_stats(hash_table* table)
{
	if (table != NULL)
	{
		printf("size    : %d\r\n", table->array_size);
		printf("empty   : %d\r\n", table->array_size - table->used_count - table->deleted_count);
		printf("deleted : %d\r\n", table->deleted_count);
		printf("used    : %d\r\n", table->used_count);
	}
}

void insert_to_table(hash_table* table, char* key, char* value)
{
	if (table != NULL && key != NULL && value != NULL)
	{
		unsigned int h = hash(key, table->m);
		unsigned int idx = find_index_of(table, key, h);

		if (idx < table->array_size)
		{
			// update cell value
			cell* c = &table->array[idx];
			free(c->value);
			c->value = value;

			free(key);
			return;
		}
		else
		{
			unsigned int i;
			for (i = table->array_step * h; i < table->array_size; ++i)
			{
				cell* c = &table->array[table->array_step * h];

				if (c->state == deleted)
				{
					if (strcmp(c->key, key) == 0)
					{
						c->state = used;
						table->used_count++;
						c->value = value;

						free(key);
						return;
					}
				}
				else if (c->state == empty)
				{
					c->state = used;
					table->used_count++;
					free(c->key);
					c->key = key;
					free(c->value);
					c->value = value;
					return;
				}
			}
		}
	}

	free(key);
	free(value);
}

void remove_from_table(hash_table* table, char* key)
{
	if (table != NULL && key != NULL)
	{
		unsigned int h = hash(key, table->m);
		unsigned int idx = find_index_of(table, key, h);

		if (idx < table->array_size)
		{
			cell* c = &table->array[idx];
			if (c->state == used) // TODO: useless if ?
			{
				table->used_count--;
				c->state = deleted;
				table->deleted_count++;

				free(c->value);
				c->value = NULL;
			}
		}
	}

	free(key);
}

void find_in_table(hash_table* table, char* key)
{
	if (table != NULL && key != NULL)
	{
		unsigned int h = hash(key, table->m);
		unsigned int idx = find_index_of(table, key, h);
		free(key);

		if (idx < table->array_size)
		{
			printf("%s\r\n", table->array[idx].value);
			return;
		}
	}

	printf("Not found\r\n");
}

static unsigned int find_index_of(hash_table* table, char* key, unsigned int h)
{
	if (table != NULL && key != NULL)
	{
		unsigned int i;
		for (i = table->array_step * h; i < table->array_size; ++i)
		{
			cell* c = &table->array[table->array_step * h];

			if (c->state == used)
			{
				if (strcmp(c->key, key) == 0)
					return i;
			}
		}
	}
	return UINT_MAX;
}

/* encodage d'une chaine de caracteres sous la forme d'un entier non signe */
static unsigned int shift_rotate(unsigned int val, unsigned int n)
{
	n = n % (sizeof(unsigned int) * 8);
	return (val << n) | (val >> (sizeof(unsigned int) * 8 - n));
}

/* fonction de hachage d'une chaine de caracteres */
static unsigned int hash(char* chaine, unsigned int m)
{
	unsigned int i;
	unsigned int h = 0;
	for (i = 0; i < strlen(chaine); i++)
	{
		h = h + shift_rotate(chaine[i], i * 7);
	}
	return h % m;
}
