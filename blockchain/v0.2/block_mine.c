#include "blockchain.h"

/**
 * block_mine - Mines a block by finding a valid nonce
 * @block: Pointer to the block to mine
 */
void block_mine(block_t *block)
{
	uint64_t nonce = 0;
	uint8_t hash[SHA256_DIGEST_LENGTH];

	while (1)
	{
		block->info.nonce = nonce;

		block_hash(block, hash);

		if (hash_matches_difficulty(hash, block->info.difficulty))
			break;

		nonce++;
	}

	memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);
}
