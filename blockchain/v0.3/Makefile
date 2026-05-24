CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3 -c -I. -Itransaction/ -Iprovided/ -I../../crypto -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
CFLAGS += -Wno-deprecated-declarations

SRC0 = blockchain_create.c blockchain_deserialize.c blockchain_destroy.c \
       blockchain_difficulty.c blockchain_serialize.c block_create.c \
       block_destroy.c block_hash.c block_is_valid.c block_mine.c \
       transaction/coinbase_create.c transaction/coinbase_is_valid.c \
       hash_matches_difficulty.c \
       transaction/transaction_create.c transaction/transaction_destroy.c \
       transaction/transaction_hash.c transaction/transaction_is_valid.c \
       transaction/tx_in_create.c transaction/tx_in_sign.c \
       transaction/tx_out_create.c transaction/unspent_tx_out_create.c \
       transaction/update_unspent.c

OBJ0 = $(SRC0:.c=.o)
NAME0 = libhblk_blockchain.a

.PHONY: clean oclean flcean libhblk_blockchain.a

clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

libhblk_blockchain.a: blockchain.h transaction/transaction.h $(OBJ0)
	ar rcs $(NAME0) $(OBJ0)
