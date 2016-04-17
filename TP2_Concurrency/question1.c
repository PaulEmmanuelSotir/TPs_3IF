#include <stdio.h>
#include <stdint.h>

void print_prime_factors(uint64_t n)
{
    uint64_t i = 0;
    uint64_t nPrime = n;
    printf("%ju : ", n);
    for( i = 2 ; i <= nPrime ; i ++)
    {
		if(nPrime%i == 0)
		{
			nPrime = nPrime/i;
			printf("%ju ", i);
			fflush(stdout);
			i = 1; 
		}
		else if(nPrime < 2 || nPrime > n)
		{
			break;
		}
	}
	printf("\r\n");
}

int main(void)
{
    print_prime_factors(77); // expected result:   77: 7 11
    print_prime_factors(84); // expected result:   84: 2 2 3 7
	
    // expected result:   429496729675917: 3 18229 7853726291
    print_prime_factors(429496729675917);

    return 0;
}
