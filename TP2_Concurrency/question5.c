#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>


static pthread_mutex_t mutexRead;

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
		
		uint64_t value=atoll(line);
		print_prime_factors(value);
	
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
	pthread_create (&ta, NULL, &print_prime_factors_thread, primeList);
	pthread_create (&tb, NULL, &print_prime_factors_thread, primeList);
	pthread_join (ta, NULL);
	pthread_join (tb, NULL);
	
    return 0;
}

