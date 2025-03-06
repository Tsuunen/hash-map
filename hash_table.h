#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

typedef struct _Node
{
	char			key[50];
	int				value;
	struct _Node	*next;
} Node;

typedef struct
{
	Node	**table;
	int		size;
} HashTable;

int			hash(char *str, int tableSize);
HashTable	*initHashTable(int tableSize);
void		freeHashTable(HashTable *tab);
void		showHashTable(HashTable *tab);
void		insert(HashTable **tab, char *key, int value);
Node		*search(HashTable *tab, char *key);
void		deleteFromHashTable(HashTable **tab, char *key);
float		loadFactor(HashTable *tab);
void		enhanceHashTableSize(HashTable **tab);
void		shrinkHashTableSize(HashTable **tab);

#endif
