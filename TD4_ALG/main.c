#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_table.h"

#define HASH_TABLE_REPETITION 1
//#define DEFAULT_HASH_TABLE_SIZE 100

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

