#include <stdlib.h>
#include <stdio.h>

#include "blockchain.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 * Author: Frank Onyema Orji
 */
int main(void)
{
	blockchain_t *blockchain;
	block_t *first, *block;

	blockchain = blockchain_create();
	first = llist_get_head(blockcahin->chain);

	block = block_create(first, (int8_t *)"Holberton", 9);
	block_hash(block, block->);
	llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

	if (block_is_valid(first, NULL) != 0 ||
			block_is_valid(block, first) != 0)
	{
		fprint(stderr, "Block invalid\n");
		return (EXIT_FAILURE);
	}
	printf("Block is valid\n");

	blockchain_destroy(blockchain);

	return (EXIT_SUCCESS);
}

