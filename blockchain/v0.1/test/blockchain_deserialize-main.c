#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 * Author: Frank Onyema Orji
 */
int main(void)
{
	blockchain = blockchain_deserialize("save.hblk");

	_blockchain_print_brief(blockchain);
	blockchain_destroy(blockchain);

	return (EXIT_SUCCESS);
}

