#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>


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

void* print_prime_factors_thread(void* n)
{
	
	uint64_t x = *((uint64_t*)n);
	
	print_prime_factors(x);
	
	return NULL;
}

int main(void)
{
		FILE* primeList;
		primeList = fopen("primes2.txt", "r");
		
		pthread_t ta;
		pthread_t tb;
		
		if(primeList == NULL)
		{
			perror("erreur ouverture fichier");
			exit(-1);
		}
		
		char line1[60];
		char line2[60];
		int fin = 1;
		while(fin == 1)
		{
			fin = 0;
			if(fgets(line1, 60, primeList) != NULL)
			{
				fin = 1;
				uint64_t i1 = atoll(line1);
				pthread_create (&ta, NULL, print_prime_factors_thread, &i1);
			}
			if(fgets(line2, 60, primeList) != NULL)
			{
				fin = 1;
				uint64_t i2 = atoll(line2);
				pthread_create (&tb, NULL, print_prime_factors_thread, &i2);
			}
			
			pthread_join (ta, NULL);
			pthread_join (tb, NULL);
		}

    return 0;
}

