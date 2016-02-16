#include "von_neumann.h"

int Dec_size(word32 e)
{
	unsigned i = 0;
	while (e != 0)
	{
		++i;
		e = e / 10;
	}
	return i;
}

word16 Von_Neumann(word16 *next)
{
	word32 result;
	int pds, i;
	result = (*next)*(*next);
	pds = Dec_size(result);
	pds = (pds - 4) / 2;
	for (i = 0; i < pds; i++)
	{
		result = (result) / 10;
	}
	result = result % 10000;
	*next = result;
	return ((word16)result);
}
