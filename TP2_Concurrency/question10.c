#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

#define MAX_FACTORS 20

typedef enum { empty, used, deleted } status;

typedef struct
{
	size_t size;
	uint64_t* factors;
} value_t;

typedef struct
{
	status state;
	uint64_t key;
	value_t value;
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

static unsigned int hash(uint64_t value, uint64_t m);
static unsigned int find_index_of(hash_table* table, uint64_t val, unsigned int h);

void init_hash_table(hash_table* table, unsigned int repetition, uint64_t m);
void destr_hash_table(hash_table* table);
void insert_to_table(hash_table* table, uint64_t key, value_t value);
void remove_from_table(hash_table* table, uint64_t key);
value_t find_in_table(hash_table* table, uint64_t key);

void init_hash_table(hash_table* table, unsigned int repetition, uint64_t m)
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

void insert_to_table(hash_table* table, uint64_t key, value_t value)
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
					if (c->key == key)
					{
						c->state = used;
						table->used_count++;
						c->value = value;
						return;
					}
				}
				else if (c->state == empty)
				{
					c->state = used;
					table->used_count++;
					c->key = key;
					free(c->value);
					c->value = value;
					return;
				}
			}
		}
	}
	free(value);
}

void remove_from_table(hash_table* table, uint64_t key)
{
	if (table != NULL)
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
}

value_t find_in_table(hash_table* table, uint64_t key)
{
	if (table != NULL)
	{
		unsigned int h = hash(key, table->m);
		unsigned int idx = find_index_of(table, key, h);
		
		if (idx < table->array_size)
			return table->array[idx].value;
	}
	return NULL;
}

static unsigned int find_index_of(hash_table* table, uint64_t key, unsigned int h)
{
	if (table != NULL)
	{
		unsigned int i;
		for (i = table->array_step * h; i < table->array_size; ++i)
		{
			cell* c = &table->array[table->array_step * h];

			if (c->state == used)
			{
				if (c->key == key)
					return i;
			}
		}
	}
	return UINT_MAX;
}

/* fonction de hachage d'une valeur sur 64 bits */
static unsigned int hash(uint64_t key, uint64_t m)
{
	return key*2654435761 % m;
}

static pthread_mutex_t mutexRead;
static pthread_mutex_t mutexWrite;
static pthread_mutex_t hash_mutex;

/*int get_prime_factors(uint64_t n, uint64_t* dest)
{
    uint64_t i = 0;
    int cpt = 0;
    uint64_t nPrime = n;
    for( i = 2 ; i <= nPrime ; i ++)
    {
		if(nPrime % i == 0)
		{
			if(cpt < MAX_FACTORS)
			{
				dest[cpt++] = i;
			}
			nPrime = nPrime/i;
			i = 1; 
		}
		else if(nPrime < 2)
		{
			break;
		}
	}
	return cpt;
}*/

int get_prime_factors(uint64_t n, uint64_t* dest)
{
    uint64_t i = 0;
    int cpt = 0;
    uint64_t nPrime = n;
    
    for( i = 2 ; i <= nPrime;)
    {
		if(nPrime % i == 0)
		{
			if(cpt < MAX_FACTORS)
			{
				dest[cpt++] = i;
			}
			
			value_t result = find_in_table(&table, nPrime);
			if(result != NULL)
			{
				memcpy(*dest[cpt], result.factors, sizeof(uint64_t*result.size));
				insert_to_table(&table, nPrime, result);
				return cpt;
			}
			
			nPrime = nPrime/i;
		}
		else if(nPrime < 2)
		{
			break;
		}
		else
			i++;
	}
	return cpt;
}

static hash_table table;

void print_prime_factors(uint64_t n)
{
    uint64_t factors[MAX_FACTORS];
	int j,k;
	k=get_prime_factors(n,factors);
	pthread_mutex_lock(&mutexWrite);
	printf("%ju: ",n);
	for(j=0; j<k; j++)
	{
		printf("%ju ",factors[j]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutexWrite);
}

void decompo_task(FILE* file)
{
	char line[60];
	
	while(1)
	{
		pthread_mutex_lock(&mutexRead);
		if(fgets(line, 60, file) == NULL)
		{
			pthread_mutex_unlock(&mutexRead);
			break;
		}
		pthread_mutex_unlock(&mutexRead);
		
		print_prime_factors(atoll(line));
	
	}
}

void* print_prime_factors_thread(void* n)
{
	FILE* x = ((FILE*)n);
	decompo_task(x);
	return NULL;
}

int main(void)
{
	init_hash_table(&table, 5, 4294967296);

	FILE* primeList;
	primeList = fopen("primes2.txt", "r");
	
	pthread_t ta;
	pthread_t tb;
	
	if(primeList == NULL)
	{
		perror("erreur ouverture fichier");
		exit(-1);
	}
	
	pthread_mutex_init(&mutexRead, NULL);
	pthread_mutex_init(&hash_mutex, NULL);
	pthread_mutex_init(&mutexWrite, NULL);
	pthread_create (&ta, NULL, &print_prime_factors_thread, primeList);
	pthread_create (&tb, NULL, &print_prime_factors_thread, primeList);
	pthread_join (ta, NULL);
	pthread_join (tb, NULL);
	
    return 0;
}

