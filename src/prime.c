#include <math.h>

#include "prime.h"

/*
 * Tells whether x is prime or not
 * 
 * Retunrs:
 * 	1 - Prime
 * 	0 - Not prime
 */

int is_prime(const int x) {
	if(x < 4) return 1;
	if(x % 2 == 0) return 0;

	for(int i = 3; i <= floor(sqrt((double) x)); i+= 2) 
		if((x % i) == 0)	
			return 0;

	return 1;
}

/*
 * Retunrns the next prime after x, or x if x is already prime
 */
int next_prime(int x) {
	while (is_prime(x) != 1)
		x++;

	return x;	
}