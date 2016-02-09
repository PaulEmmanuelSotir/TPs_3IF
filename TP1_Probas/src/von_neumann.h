#ifndef VON_NEUMANN_H
#define VON_NEUMANN_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "mersenne_twister.h"
#include "aes.h"

typedef unsigned int word32;
typedef uint16_t word16;
typedef unsigned char word8;

// cette fonction permet de connaitre la taille décimale d'un nombre nécessaire pour le calcul de VON NEUMANN
int Dec_size(word32 e);
// =============================VON NEUMANN =============================
// next est au premier clock la graine et ensuite l'état courant du générateur de Von Neumann. La graine devra faire 4 chiffres décimaux.
// la sortie de la fonction est également un mot de 4 chiffres décimaux.
word16 Von_Neumann(word16 *next);

#endif

