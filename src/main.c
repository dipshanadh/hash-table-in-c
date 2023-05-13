#include <stdio.h>

#include "hash_table.h"

int main() {
	ht_hash_table *ht = ht_new();

	ht_insert(ht, "name", "Dipshan Adhikari");
	ht_insert(ht, "country", "Nepal");
	ht_insert(ht, "hobby", "programming");

	printf("%s\n", ht_search(ht, "name"));
	printf("%s\n", ht_search(ht, "hobby"));

	ht_del_hash_table(ht);

	return 0;
}