#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_TABLE_REPETITION 1
//#define DEFAULT_HASH_TABLE_SIZE 100

typedef enum { empty, used, deleted } status;

typedef struct
{
	status state;
	char* key;
	char* value;
} cell;

typedef struct
{
	unsigned int m;
	cell* array;
	unsigned int array_step;
	unsigned int array_size;
	unsigned int deleted_count;
	unsigned int used_count;
} hash_table;

void init_hash_table(hash_table* table, unsigned int repetition, unsigned int m);
void destr_hash_table(hash_table* table);
void show_stats(hash_table* table);
void insert_to_table(hash_table* table, char* key, char* value);
void remove_from_table(hash_table* table, char* key);
void find_in_table(hash_table* table, char* key);

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
	return 65535;
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

void error(void);

int main(void) 
{
   int size;
   char lecture[100];
   
   char * key;
   char * val;
   hash_table table;

   if (fscanf(stdin,"%99s", lecture)!=1)
      error();
   while (strcmp(lecture,"bye")!=0)
   {
      if (strcmp(lecture,"init")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         size = atoi(lecture);
		 
         // code d'initialisation
		 init_hash_table(&table, HASH_TABLE_REPETITION, size);
      }
      else if (strcmp(lecture,"insert")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         val = strdup(lecture);
		 
         // insertion
		 insert_to_table(&table, key, val);
      }
      else if (strcmp(lecture,"delete")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
		 
         // suppression
		 remove_from_table(&table, key); 
      }
      else if (strcmp(lecture,"query")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
			
         // recherche et affiche le resultat
		 find_in_table(&table, key);		 
      }
      else if (strcmp(lecture,"destroy")==0)
      {
         // destruction
		 destr_hash_table(&table);
      }
      else if (strcmp(lecture,"stats")==0)
      {
         // statistiques
		 show_stats(&table);
      }

      if (fscanf(stdin,"%99s",lecture)!=1)
         error();
   }
   return 0;
}

void error(void)
{
   printf("input error\r\n");
   exit(0);
}

