#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_prime_factors(uint64_t n)
{
    uint64_t i = 0;
    uint64_t nPrime = n;
    printf("%ju: ", n);
    for( i = 2 ; i <= nPrime ; i ++)
    {
		if(nPrime%i == 0)
		{
			nPrime = nPrime/i;
			printf("%ju ", i);
			i = 1; 
		}
		else if(nPrime < 2)
		{
			break;
		}
	}
	printf("\r\n");
}

int main(void)
{
		FILE* primeList;
		primeList = fopen("primes2.txt", "r");
		
		if(primeList == NULL)
		{
			perror("erreur ouverture fichier");
			exit(-1);
		}
		
		char line[60];
		while(fgets(line, 60, primeList) != NULL)
		{
			print_prime_factors(atoll(line));
		}

    return 0;
}
