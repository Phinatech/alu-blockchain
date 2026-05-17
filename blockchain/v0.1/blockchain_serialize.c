#include "blockchain.h"
#include <fcntl.h>
#include <unistd.h>


int block_serialize(llist_node_t node_ptr, int idx, void *arg);

/**
*  blockchain_serialize - serializes a blockchain into a file
*
* @blockchain: pointer to the Blockchain structure to be serialized
* @path: path to a file
*
* Return: 0 if successful, -1 if failed
*/
int blockchain_serialize(blockchain_t const *blockchain,

char const *path)
{
	FILE *file;
	hblk_file_t file_header;


	if (!blockchain || !path)
		return (-1);

	/*Set header values*/
	memcpy(file_header.hblk_magic, HBLK_MAGIC, strlen(HBLK_MAGIC));
	memcpy(file_header.hblk_version, HBLK_VERSION, strlen(HBLK_VERSION));
	file_header.hblk_endian = _get_endianness();
	file_header.hblk_blocks = llist_size(blockchain->chain);

	if (file_header.hblk_blocks == -1)
		return (-1);

	file = fopen(path, "w");
	if (!file)
		return (-1);

	fwrite(&file_header, sizeof(file_header), 1, file);

	llist_for_each(blockchain->chain, (node_func_t)block_serialize, file);

	fclose(file);
	return (0);
}


/**
* block_serialize - serializes a block into a file
* @node_ptr: pointer to the node to serialize
* @idx: index of the node
* @arg: file descriptor
* Return: 0 if successful, -1 if failed
*/
int block_serialize(llist_node_t node_ptr, int idx, void *arg)
{
	block_t *block = (block_t *)node_ptr;
	FILE *file = (FILE *)arg;

	if (!block || !file)
		return (-1);

	/*unused var*/
	(void)idx;

	fwrite((void *)&block->info, sizeof(block->info), 1, file);
	fwrite((void *)&block->data.len, sizeof(block->data.len), 1, file);
	fwrite(block->data.buffer, block->data.len, 1, file);
	fwrite(block->hash, sizeof(block->hash), 1, file);
	return (sizeof(*block));
}
