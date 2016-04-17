#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FACTORS 20

static pthread_mutex_t mutexRead;
static pthread_mutex_t mutexWrite;


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
	pthread_mutex_init(&mutexWrite, NULL);
	pthread_create (&ta, NULL, &print_prime_factors_thread, primeList);
	pthread_create (&tb, NULL, &print_prime_factors_thread, primeList);
	pthread_join (ta, NULL);
	pthread_join (tb, NULL);
	
    return 0;
}

