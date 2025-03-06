#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	HashTable	*hashTable = initHashTable(2);

	/* printf("%p\n", hashTable.table); */
	insert(&hashTable, "test", 1);
	/* insert(hashTable, "test", 1); */
	insert(&hashTable, "testb", 2);
	insert(&hashTable, "testc", 3);
	/* insert(hashTable, "testd", 4); */
	/* insert(hashTable, "teste", 5); */
	/* insert(hashTable, "testf", 6); */
	/* insert(hashTable, "testg", 7); */
	/* insert(hashTable, "testh", 8); */

	/* enhanceHashTableSize(&hashTable); */
	showHashTable(hashTable);

	freeHashTable(hashTable);
	return (0);
}
