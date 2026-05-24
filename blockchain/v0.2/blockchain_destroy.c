#include "blockchain.h"


/**
* blockchain_destroy - deletes an existing Blockchain.
*
* @blockchain: pointer to the Blockchain structure to delete.
* Author: Frank Onyema Orji.
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	block_t *block, *tmp;

	block = llist_pop(blockchain->chain);
	while (block != NULL)
	{
		tmp = block;
		block = llist_pop(blockchain->chain);
		block_destroy(tmp);
	}
	llist_destroy(blockchain->chain, 0, NULL);
	free(blockchain);
}

