#include "blockchain.h"

/* GENESIS_BLOCK - first block in the blockchain */
#define GENESIS_BLOCK                                                    \
	{                                                                          \
		{                                                                      \
			0 /* index */,                                                     \
			0,			/* difficulty */                                       \
			1537578000, /* timestamp */                                        \
			0,			/* nonce */                                            \
			{0}			/* prev_hash */                                        \
		},                                                                     \
			{                                                                  \
				"Holberton School", /* buffer */                               \
				16					/* len */                                  \
			},						/* hashed data */                          \
			"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d" \
			"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03" \
	}

/**
 * block_is_valid - checks if this and previous block are valid.
 * @block: pointer to this block in the chain.
 * @prev_block: pointer to previous block in the chain or NULL.
 * Return: 0 if valid else 1 if invalid.
 * Author: Frank Onyema Orji.
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t const _genesis = GENESIS_BLOCK;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &_genesis, sizeof(_genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);
	return (0);
}

