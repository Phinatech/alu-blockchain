#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../crypto/hblk_crypto.h"

/**
 * Author: Frank Onyema Orji
 */
void _print_hex_buffer(unint8_t const *buf, size_t len);

/**
 * main - Entry Point
 * @ac Arguments Counter
 * @av: Arguments Vector
 * Return: EXIT_SUCCESS OR EXIT_FAILURE
 */
int main(int ac, char **av)
{
	unint8_t hash[SHA256_DIGEST_LENGTH];
	unint8_t *test_ptr;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s arg\n", av[0]);
		return (FAILURE);
	}

	/*Test `sha256()` */
	test_ptr = sha256((int8_t *)av[1], strlen(av[1]), hash);
	if (!test_ptr)
	{
		fprintf(stderr, "sha256() failed\n");
		return (EXIT_FAILURE);
	}
	if (test_ptr != hash)
	{
		fprintf(stderr, "Return value and pointer differ\n");
		return (EXIT_FAILURE);
	}

	printf("\"%s\" hash is: ", av[1]);
	_print_hex_buffer(hash, SHA_DIGEST_LENGHT);
	printf("\n");

	return (EXIT_SUCESS);
}