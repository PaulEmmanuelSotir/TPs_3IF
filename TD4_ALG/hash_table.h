#ifndef HASH_TABLE_H
#define HASH_TABLE_H

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

#endif /* HASH_TABLE_H */
