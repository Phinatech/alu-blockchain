#include "blockchain.h"

/**
 * block_destroy - deletes an exisiting block
 *
 * @block: pointer to the block to delete
 * Author: Frank Onyema Orji
 */
void block_destroy(block_t *block)
{
	free(block);
}

