#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

#define HT_PRIME_1 151
#define HT_PRIME_2 163

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(const char *k, const char *v) {
	ht_item *i 	= malloc(sizeof(ht_item));

	i->key 		= strdup(k);
	i->value	= strdup(v);

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

static int ht_hash(const char *s, const int a, const int m) {
	long hash = 0;
	const int len_s = strlen(s);

	for(int i = 0; i < len_s; i++) {
		hash += (long)pow(a, len_s - (i + 1)) * s[i];
		hash = hash % m;
	}

	return (int)hash;
}

static int ht_get_hash(
	const char *s, const int num_bucekts, const int attempts
) {
	const int hash_a = ht_hash(s, HT_PRIME_1, num_bucekts);
	const int hash_b = ht_hash(s, HT_PRIME_2, num_bucekts);

	return (hash_a + (attempts * (hash_b + 1))) % num_bucekts;
}

void ht_insert(ht_hash_table *ht, const char *key, const char *value) {
	ht_item *item = ht_new_item(key, value);
	ht_item *curr_item;

	int index;
	int i = 0;
	
	do {
		index		= ht_get_hash(item->key, ht->size, i);
		curr_item 	= ht->items[index];

		if(curr_item != NULL && strcmp(curr_item->key, key) == 0) {
			ht_del_item(curr_item);
			ht->items[index] = item;
			return;
		}

		i++;
	} while(curr_item != NULL && curr_item != &HT_DELETED_ITEM);

	ht->items[index] = item;
	ht->count++;
}

char *ht_search(ht_hash_table *ht, const char *key) {
	ht_item *item;

	int index;
	int i = 0;
	
	do {
		index 	= ht_get_hash(key, ht->size, i);
		item	= ht->items[index];

		if(strcmp(item->key, key) == 0)
			return item->value;

		i++;
	} while(item != NULL && item != &HT_DELETED_ITEM);

	return NULL;
}

void ht_delete(ht_hash_table *ht, const char *key) {
	ht_item *item;

	int index;
	int i = 0;

	do {
		index	= ht_get_hash(key, ht->size, i);
		item	= ht->items[index];

		if(item != &HT_DELETED_ITEM)
			if(strcmp(item->key, key) == 0) {
				ht_del_item(item);
				ht->items[index] = &HT_DELETED_ITEM;
			}

		i++;
	} while(item != NULL);

	ht->count--;
}