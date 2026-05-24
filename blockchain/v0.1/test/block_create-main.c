#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_print(blockchain_t const *blockchain);

void _blockchain_destroy(blockain_t *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS OR EXIT_FAILURE
 * Author: Frank Onyema Orji
 */

int main(void)
{
	blockchain_t *blockchain;
	block_t *block;

	block = block_create(block, (int8_t *)"Holberton", 9);
	llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	block = block_create(block, (int8_t *)"School", 6);
	llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

	_blockchain_print(blockchain);
	_blockchain_destroy(blockchain);

	return (EXIT_SUCCESS);
}

