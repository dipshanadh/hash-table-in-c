#include <stdio.h>

#include "hash_table.h"

int main() {
	/*
	 * Initialize a hash table
	 */
	ht_hash_table *ht = ht_new();

	/*
	 * Insert items as "key": "value" pairs
	 */
	ht_insert(ht, "name", "Dipshan Adhikari");
	ht_insert(ht, "country", "Nepal");
	ht_insert(ht, "hobby", "programming");

	/*
	 * Search for items using key
	 */
	printf("%s\n", ht_search(ht, "name"));
	printf("%s\n", ht_search(ht, "country"));
	printf("%s\n", ht_search(ht, "hobby"));

	/*
	 * Update items
	 */
	ht_insert(ht, "hobby", "coding");
	printf("\n%s", ht_search(ht, "hobby"));


	/*
	 * Delete the hash table
	 */
	ht_del_hash_table(ht);

	return 0;
}