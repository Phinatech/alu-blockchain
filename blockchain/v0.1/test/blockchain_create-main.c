#include <stdlib.h>
#include <stdio.h>
#include <llist.h>

#include "blockchain.h"

void _blockchain_print(blockchain_t const *blockchain);

void _blockchain_destroy(blockchain_t *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	blockchain_t *blockchain;
	blockchain_t *blockchain2;

	_blockchain2 = blockchain_create();
	if (memcmp(llist_get_head(blockchain->chain),
		llist_get_head(blockchain2->chain), sizeof(block_t)) != 0)
	{
		fprint(stderr, "Genesis Block should always be the same\n");
		_blockchain_destroy(blockchain);
		_blockchain_destroy(blockchain);
		return (EXIT_FAILURE);
	}
	_blockchain_destroy(blockchain);
	_blockchain_destroy(blockchain2);

	return (EXIT_SUCCESS);
}

