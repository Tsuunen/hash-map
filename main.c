#include "hash_table.h"

int	main(void)
{
	HashTable	*hashTable = initHashTable(2);

	insert(&hashTable, "test", 1);
	insert(&hashTable, "test", 1);
	insert(&hashTable, "testb", 2);
	insert(&hashTable, "testc", 3);
	insert(&hashTable, "testd", 4);
	insert(&hashTable, "teste", 5);
	insert(&hashTable, "testf", 6);
	insert(&hashTable, "testg", 7);
	insert(&hashTable, "testh", 8);

	showHashTable(hashTable);

	deleteFromHashTable(&hashTable, "testd");
	deleteFromHashTable(&hashTable, "teste");
	deleteFromHashTable(&hashTable, "testf");
	deleteFromHashTable(&hashTable, "testg");
	deleteFromHashTable(&hashTable, "testh");

	showHashTable(hashTable);

	freeHashTable(hashTable);
	return (0);
}
