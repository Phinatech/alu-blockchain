#include "hblk_crypto.h"

/**
 * ec_create - create a new EC key pair.
 *
 * Return: Pointer to the created EC key pair,or NULL upon failure.
 * Author: Frank Onyema Orji.
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key = NULL;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	if (!EC_KEY_generate_key(key))
	{
		EC_KEY_free(key);
		return (NULL);
	}
	return (key);
}
