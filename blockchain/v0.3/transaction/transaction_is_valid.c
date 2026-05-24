#include "transaction.h"

int match_unspent(llist_node_t node, void *arg)
{
	unspent_tx_out_t *utxo = node;
	tx_in_t *txi = arg;

	if (!memcmp(txi->tx_out_hash, utxo->out.hash, SHA256_DIGEST_LENGTH))
		return (1);
	return (0);
}

int check_inputs(llist_node_t node, unsigned int idx, void *arg)
{
	tx_in_t *txi = node;
	validation_vistor_t *visitor = arg;
	unspent_tx_out_t *utxo =
		llist_find_node(visitor->all_unspent, match_unspent, txi);
	EC_KEY *key;

	if (!utxo)
	{
		dprintf(2, "check_inputs: utxo NULL\n");
		visitor->valid = 0;
		return (1);
	}
	if (llist_find_node(visitor->used_utxos, match_unspent, txi))
	{
		dprintf(2, "check_inputs: double spend detected\n");
		visitor->valid = 0;
		return (1);
	}
	llist_add_node(visitor->used_utxos, utxo, ADD_NODE_REAR);
	key = ec_from_pub(utxo->out.pub);
	if (!key ||
		!ec_verify(key, visitor->tx->id, SHA256_DIGEST_LENGTH, &txi->sig))
	{
		dprintf(2, "check_inputs: key error\n");
		visitor->valid = 0;
		return (EC_KEY_free(key), 1);
	}
	EC_KEY_free(key);
	visitor->in_amount += utxo->out.amount;
	return (0);
	(void)idx;
}

int check_outputs(llist_node_t node, unsigned int idx, void *arg)
{
	tx_out_t *txo = node;
	validation_vistor_t *visitor = arg;

	visitor->out_amount += txo->amount;
	return (0);
	(void)idx;
}

int transaction_is_valid(transaction_t const *transaction,
	llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	validation_vistor_t visitor = {0};

	if (!transaction || !all_unspent)
		return (0);
	if (!llist_size(transaction->inputs) || !llist_size(transaction->outputs))
		return (0);
	visitor.tx = transaction;
	visitor.all_unspent = all_unspent;
	visitor.used_utxos = llist_create(MT_SUPPORT_FALSE);
	visitor.valid = 1;
	if (!visitor.used_utxos)
		return (0);
	if (!transaction_hash(transaction, hash_buf))
		return (llist_destroy(visitor.used_utxos, 0, NULL), 0);
	if (memcmp(transaction->id, hash_buf, SHA256_DIGEST_LENGTH))
		return (llist_destroy(visitor.used_utxos, 0, NULL), 0);
	if (llist_for_each(transaction->inputs, check_inputs, &visitor) ||
		!visitor.valid)
		return (llist_destroy(visitor.used_utxos, 0, NULL), 0);
	if (llist_for_each(transaction->outputs, check_outputs, &visitor) ||
		visitor.in_amount != visitor.out_amount || !visitor.in_amount)
		return (llist_destroy(visitor.used_utxos, 0, NULL), 0);
	llist_destroy(visitor.used_utxos, 0, NULL);
	return (1);
}
