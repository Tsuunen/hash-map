#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	hash(char *str, int tableSize)
{
	int	sum = 0;

	while (*str != 0)
	{
		sum += *str;
		str++;
	}

	return (sum % tableSize);
}

HashTable	*initHashTable(int tableSize)
{
	int	i = 0;
	HashTable	*tab = malloc(sizeof(HashTable));
	if (tab == NULL)
		return (NULL);

	tab->size = tableSize;
	tab->table = malloc(sizeof(Node*) * tableSize); 
	if (tab->table == NULL)
	{
		free(tab);
		return (NULL);
	}

	while (i < tableSize)
	{
		tab->table[i] = NULL;
		i++;
	}

	return (tab);
}

void	freeHashTable(HashTable *tab)
{
	Node	*curr;
	Node	*aux;
	int		i = 0;

	while (i < tab->size)
	{
		curr = (tab->table)[i];
		while (curr != NULL)
		{
			aux = curr;
			curr = curr->next;
			free(aux);
		}
		i++;
	}

	free(tab->table);
	free(tab);
}

void	showHashTable(HashTable *tab)
{
	Node	*curr;
	int		i = 0;

	while (i < tab->size)
	{
		printf("%d : \n", i);
		curr = (tab->table)[i];
		while (curr != NULL)
		{
			printf("%s -> %d\n", curr->key, curr->value);
			curr = curr->next;
		}
		printf("\n");
		i++;
	}
}

void	insert(HashTable **tab, char *key, int value)
{
	HashTable	*tmp = *tab;
	int		 	hashedKey = hash(key, tmp->size);
	Node		*new = malloc(sizeof(Node));
	if (new == NULL)
		return ;

	if (search(tmp, key) != NULL)
	{
		free(new);
		return ;
	}

	strcpy(new->key, key);
	new->value = value;

	new->next = tmp->table[hashedKey];
	tmp->table[hashedKey] = new;

	if (loadFactor(tmp) >= 0.75)
		enhanceHashTableSize(tab);
}

Node	*search(HashTable *tab, char *key)
{
	int		hashedKey = hash(key, tab->size);
	Node	*curr = tab->table[hashedKey];

	while (curr != NULL)
	{
		if (!strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	deleteFromHashTable(HashTable **tab, char *key)
{
	HashTable	*tmp = *tab;
	int			hashedKey = hash(key, tmp->size);
	Node		*curr = tmp->table[hashedKey];
	Node		*aux = NULL;

	if (curr == NULL)
		return ;
	if (!strcmp(curr->key, key))
	{
		aux = curr;
		tmp->table[hashedKey] = curr->next;
		free(aux);
		if (loadFactor(tmp) <= 0.45)
			shrinkHashTableSize(tab);
		return ;
	}
	while (curr->next != NULL)
	{
		if (!strcmp(curr->next->key, key))
		{
			aux = curr->next;
			curr->next = curr->next->next;
			free(aux);
			if (loadFactor(tmp) <= 0.45)
				shrinkHashTableSize(tab);
			return ;
		}
		curr = curr->next;
	}

}

float	loadFactor(HashTable *tab)
{
	int	i = 0;
	int	usedRow = 0;

	while (i < tab->size)
	{
		if (tab->table[i] != NULL)
			usedRow++;
		i++;
	}
	
	return ((float)usedRow / (float)tab->size);
}

void    enhanceHashTableSize(HashTable **tab)
{
	HashTable	*new = NULL;
	HashTable	*tmp = *tab;
	int			i = 0;
	Node		*curr;

	new = initHashTable(tmp->size * 2);

	while (i < tmp->size)
	{
		curr = tmp->table[i];
		while (curr != NULL)
		{
			insert(&new, curr->key, curr->value);
			curr = curr->next;
		}
		i++;
	}

	*tab = new;
	freeHashTable(tmp);
}

void	shrinkHashTableSize(HashTable **tab)
{
	HashTable	*new = NULL;
	HashTable	*tmp = *tab;
	int			i = 0;
	Node		*curr;

	new = initHashTable(tmp->size / 2);

	while (i < tmp->size)
	{
		curr = tmp->table[i];
		while (curr != NULL)
		{
			insert(&new, curr->key, curr->value);
			curr = curr->next;
		}
		i++;
	}

	*tab = new;
	freeHashTable(tmp);
}
