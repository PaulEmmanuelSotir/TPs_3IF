#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * La racine se situe � l'index 0
 * Soit un n�ud � l'index i alors son fils gauche est � l'index 2i+1 et son fils droit � 2i+2
 * Soit un n�ud � l'index i>0 alors son p�re est � l'index (i-1)/2
*/

typedef struct node
{
	int value;
	struct node* left;
	struct node* right;
} node;

node* make_list();

node* insert(node* list, int value);

void remove(node* list, int value);

void display(node* list);

void dispose(node* list);

int main(int argc, const char* argv[])
{


	return 0;
}