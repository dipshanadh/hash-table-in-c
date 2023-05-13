#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char *key, const char *value) {
	ht_item *i 	= malloc(sizeof(ht_item));

	i->key 		= strdup(key);
	i->value	= strdup(value);

	return i;
}

static void ht_del_item(ht_item *i) {
	free(i->key);
	free(i->value);
	free(i);
}

ht_hash_table *ht_new() {
	ht_hash_table *ht = malloc(sizeof(ht_hash_table));

	ht->size 	= 64;
	ht->count 	= 0;
	ht->items	= calloc((size_t)ht->size, sizeof(ht_item));

	return ht;
}

void ht_del_hash_table(ht_hash_table *ht) {
	for(int i = 0; i < ht->size; i++) {
		ht_item *item = ht->items[i];

		if(item != NULL)
			ht_del_item(item);
	}

	free(ht->items);
	free(ht);
}