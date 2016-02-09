/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
   
/*
 * Benjamin Pousse, XLIM - Université de Limoges
 * benjamin.pousse@xlim.fr
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define NB 4
#define NR 10
#define NK 4


#ifndef AES_H
#define AES_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define NB 4
#define NR 10
#define NK 4



#if NB == 4

#define C1 1
#define C2 2
#define C3 3

#elif NB == 5

#define C1 1
#define C2 2
#define C3 3

#elif NB == 6

#define C1 1
#define C2 2
#define C3 3

#elif NB == 7

#define C1 1
#define C2 2
#define C3 4

#elif NB == 8

#define C1 1
#define C2 3
#define C3 4

#endif

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint_fast8_t uf8;
typedef uint_fast32_t uf32;


void KeyExpansion(u32* Key_ex, const u32* Key);
void Round(u32* r, const u32* x, const u32* Key_ex);
void memxor(u32* dest, const u32* src);
void memmask(u8* dest, const u8 mask);
void memrem(u8* dest, const u8 pat);
void init_rand(u32* key, u32* plain, const size_t nk, const size_t nb, int params);
u32 AES(u32* Px, const u32* Kex);

#endif
