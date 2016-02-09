#include "von_neumann.h"
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
	word32 result = (*next)*(*next);
	int pds = (Dec_size(result) - 4) / 2;

	for (int i = 0; i < pds; ++i)
		result = (result) / 10;

	result %= 10000;
	*next = result;

	return static_cast<word16>(result);
}
