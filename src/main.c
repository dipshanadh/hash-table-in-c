#include <stdio.h>

#include "hash_table.h"

int main() {
	printf("Creating a hash table...\n");
	ht_hash_table *ht = ht_new();

	printf("Destroying a hash table...\n");
	ht_del_hash_table(ht);

	return 0;
}