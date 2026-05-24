#include "blockchain.h"


/**
* block_create - creates a Block structure and initializes it.
*
* @prev: pointer to the previous Block in the Blockchain.
* @data: pointer to a memory area to duplicate in the Block’s data.
* @data_len: number of bytes to duplicate in data.
*
* Return: pointer to the allocated Block, or NULL upon failure.
* Author: Frank Onyema Orji.
*/
block_t *block_create(block_t const *prev, int8_t const *data,

	uint32_t data_len)
{
	block_t *block;

	block = calloc(1, sizeof(*block));
	if (block == NULL)
		return (NULL);
	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.timestamp = time(NULL);
	block->info.nonce = 0;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, data, data_len);
	block->data.len = data_len;
	return (block);
}

