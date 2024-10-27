#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BLOCK_SIZE 15                    // cantidad de bloque a reservar para memoria dinamica
#define MIN(a, b) ((a) < (b) ? (a):(b))

typedef struct
{
    int id;                               // identificador de la transaccion
    int amount;                           // monto de la transaccion
    char *sender;                         // emisor de la transaccion
    char *receiver;                       // receptor de la transaccion
} S_Transaction;

typedef struct
{
    S_Transaction *transactions;          // transacciones del bloque
    unsigned int size;                    // cantidad de transacciones en el bloque
    unsigned int amount;                  // monto total de las transacciones para el bloque
} S_Block;

typedef struct
{
    S_Block *blocks;                      // bloques de la blockchain
    unsigned int transactions_per_block;  // cantidad maxima de transacciones por bloque
    unsigned int max_transaction_amount;  // monto maximo por transaccion
    unsigned int size;                    // cantidad de bloques
} S_Blockchain;

void free_blockchain(S_Blockchain *blockchain)
{
    for(int i = 0; i < blockchain->size; ++i) {
        for(int j = 0; j < blockchain->blocks[i].size; ++j) {
            free(blockchain->blocks[i].transactions[j].sender);
            free(blockchain->blocks[i].transactions[j].receiver);
        }
        free(blockchain->blocks[i].transactions);
    }
    free(blockchain->blocks);
    free(blockchain);
}

void resize_bc(S_Blockchain * myBc) {
    unsigned int block_id = myBc->size;
    myBc->size += BLOCK_SIZE;
    myBc->blocks = realloc(myBc->blocks, sizeof(S_Block) * myBc->size);
    // Luego va a haber que resizear el ultimo tam de transactions
    for(; block_id < myBc->size; ++block_id) {
        myBc->blocks[block_id].transactions = malloc(sizeof(S_Transaction) * myBc->transactions_per_block);
        myBc->blocks[block_id].size = 0;
        myBc->blocks[block_id].amount = 0;
    }
}

void append_x(S_Blockchain * myBc, int * actual_tc, const char *sender, const char *receiver, int amount, unsigned int id) {
    // actual tc / transactions_per block me va a dar el nro de bloque a usar
    // actual tc % transactions_per bloock me va a dar el numero de transaccion dentro del bloque a usar
    int block_id = (*actual_tc) / myBc->transactions_per_block, trans_id, sub_amount;
    // Cantidad de micro transacciones necesarias para almacenar amount
    /* unsigned int local_tcounter = ceil((double)amount/(myBc->max_transaction_amount)); */
    // Cantidad de bloques necesarios para almacenar la transaccion
    /* unsigned int local_bcounter = ceil((double)local_tcounter/myBc->transactions_per_block); */
    do {
        sub_amount = MIN(myBc->max_transaction_amount, amount);
        amount -= sub_amount;
        block_id = (*actual_tc) / myBc->transactions_per_block;
        trans_id = (*actual_tc) % myBc->transactions_per_block;
        if(block_id == myBc->size)
            resize_bc(myBc);
        myBc->blocks[block_id].size++;
        myBc->blocks[block_id].amount += sub_amount;
        myBc->blocks[block_id].transactions[trans_id].amount = sub_amount;
        myBc->blocks[block_id].transactions[trans_id].sender = malloc(strlen(sender) + 1);
        strcpy(myBc->blocks[block_id].transactions[trans_id].sender, sender);
        myBc->blocks[block_id].transactions[trans_id].receiver = malloc(strlen(receiver) + 1);
        strcpy(myBc->blocks[block_id].transactions[trans_id].receiver, receiver);
        myBc->blocks[block_id].transactions[trans_id].id = id;
        ++*actual_tc;
    } while(amount > 0);
}

void free_extra_space(S_Block * blocks, unsigned int size, unsigned int new_size) {
    while(new_size < size) {
        free(blocks[new_size++].transactions);
    }
}

void append_transactions(S_Blockchain * myBc, const char **senders, const char **receivers, const int *amounts, unsigned int transactions) {
    int tc = 0, actual_tc = 0;
    // ts va a llevar la cuenta de cuantas transacciones de las que me pasaron anote
    // No tiene nada que ver con el numero de bloque que estoy usando
    while(tc < transactions){
        if(amounts[tc] >= 0)
            append_x(myBc, &actual_tc, senders[tc], receivers[tc], amounts[tc], tc);
        ++tc;
    }
    unsigned int real_size = ceil((double)actual_tc/myBc->transactions_per_block);
    free_extra_space(myBc->blocks, myBc->size, real_size);
    myBc->size = real_size;
    myBc->blocks = realloc(myBc->blocks, sizeof(S_Block) * myBc->size);
    myBc->blocks[myBc->size - 1].transactions = realloc(myBc->blocks[myBc->size - 1].transactions, sizeof(S_Transaction) * myBc->blocks[myBc->size - 1].size);
}

S_Blockchain *create_blockchain(const char **senders, const char **receivers, const int *amounts, unsigned int transactions,
                                unsigned int transactions_per_block, unsigned int max_transaction_amount) {
    // transactions coincide con la longitud de *senders, *receivers y amounts
    S_Blockchain * new_bc = malloc(sizeof(*new_bc));
    new_bc->transactions_per_block = transactions_per_block;
    new_bc->max_transaction_amount = max_transaction_amount;
    new_bc->blocks = NULL;
    new_bc->size = 0;
    append_transactions(new_bc, senders, receivers, amounts, transactions);
    return new_bc;
}

int main(void)
{
    S_Blockchain *blockchain;
    unsigned int transactions;
    unsigned int transactions_per_block;
    unsigned int max_transaction_amount;

    // Ejemplo 1
    const char * senders1[3] = {"A", "B", "C"};
    const char * receivers1[3] = {"D", "E", "F"};
    const int amounts1[3] = {100, 200, 300};
    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 150;

    blockchain = create_blockchain(senders1, receivers1, amounts1, transactions, transactions_per_block, max_transaction_amount);

    assert(blockchain->size == 3);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 150);

    assert(blockchain->blocks[0].size == 2);
    assert(blockchain->blocks[0].amount == 250);

    assert(blockchain->blocks[0].transactions[0].id == 0);
    assert(blockchain->blocks[0].transactions[0].amount == 100);
    assert(strcmp(blockchain->blocks[0].transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks[0].transactions[1].id == 1);
    assert(blockchain->blocks[0].transactions[1].amount == 150);
    assert(strcmp(blockchain->blocks[0].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[1].size == 2);
    assert(blockchain->blocks[1].amount == 200);

    assert(blockchain->blocks[1].transactions[0].id == 1);
    assert(blockchain->blocks[1].transactions[0].amount == 50);
    assert(strcmp(blockchain->blocks[1].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[0].receiver, "E") == 0);


    assert(blockchain->blocks[1].transactions[1].id == 2);
    assert(blockchain->blocks[1].transactions[1].amount == 150);
    assert(strcmp(blockchain->blocks[1].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[2].size == 1);
    assert(blockchain->blocks[2].amount == 150);

    assert(blockchain->blocks[2].transactions[0].id == 2);
    assert(blockchain->blocks[2].transactions[0].amount == 150);
    assert(strcmp(blockchain->blocks[2].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[0].receiver, "F") == 0);

    free_blockchain(blockchain);

    // Ejemplo 3
    const char *senders3[3] = {"A", "B", "C"};
    const char *receivers3[3] = {"D", "E", "F"};
    const int amounts3[3] = {100, 200, 300};
    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 60;

    blockchain = create_blockchain(senders3, receivers3, amounts3, transactions, transactions_per_block, max_transaction_amount);
    assert(blockchain->size == 6);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 60);

    assert(blockchain->blocks[0].size == 2);
    assert(blockchain->blocks[0].amount == 100);

    assert(blockchain->blocks[0].transactions[0].id == 0);
    assert(blockchain->blocks[0].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[0].transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks[0].transactions[1].id == 0);
    assert(blockchain->blocks[0].transactions[1].amount == 40);
    assert(strcmp(blockchain->blocks[0].transactions[1].sender, "A") == 0);
    assert(strcmp(blockchain->blocks[0].transactions[1].receiver, "D") == 0);

    assert(blockchain->blocks[1].size == 2);
    assert(blockchain->blocks[1].amount == 120);

    assert(blockchain->blocks[1].transactions[0].id == 1);
    assert(blockchain->blocks[1].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[1].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[0].receiver, "E") == 0);


    assert(blockchain->blocks[1].transactions[1].id == 1);
    assert(blockchain->blocks[1].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[1].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[1].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[2].size == 2);
    assert(blockchain->blocks[2].amount == 80);

    assert(blockchain->blocks[2].transactions[0].id == 1);
    assert(blockchain->blocks[2].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[2].transactions[0].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[0].receiver, "E") == 0);

    assert(blockchain->blocks[2].transactions[1].id == 1);
    assert(blockchain->blocks[2].transactions[1].amount == 20);
    assert(strcmp(blockchain->blocks[2].transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks[2].transactions[1].receiver, "E") == 0);

    assert(blockchain->blocks[3].size == 2);
    assert(blockchain->blocks[3].amount == 120);

    assert(blockchain->blocks[3].transactions[0].id == 2);
    assert(blockchain->blocks[3].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[3].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[3].transactions[0].receiver, "F") == 0);

    assert(blockchain->blocks[3].transactions[1].id == 2);
    assert(blockchain->blocks[3].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[3].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[3].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[4].size == 2);
    assert(blockchain->blocks[4].amount == 120);

    assert(blockchain->blocks[4].transactions[0].id == 2);
    assert(blockchain->blocks[4].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[4].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[4].transactions[0].receiver, "F") == 0);

    assert(blockchain->blocks[4].transactions[1].id == 2);
    assert(blockchain->blocks[4].transactions[1].amount == 60);
    assert(strcmp(blockchain->blocks[4].transactions[1].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[4].transactions[1].receiver, "F") == 0);

    assert(blockchain->blocks[5].size == 1);
    assert(blockchain->blocks[5].amount == 60);

    assert(blockchain->blocks[5].transactions[0].id == 2);
    assert(blockchain->blocks[5].transactions[0].amount == 60);
    assert(strcmp(blockchain->blocks[5].transactions[0].sender, "C") == 0);
    assert(strcmp(blockchain->blocks[5].transactions[0].receiver, "F") == 0);

    free_blockchain(blockchain);

    // Ejemplo 5
    const char *senders5[3] = {"A", "B", "C"};
    const char *receivers5[3] = {"D", "E", "F"};
    const int amounts5[3] = {0, 4, -9};

    transactions = 3;
    transactions_per_block = 2;
    max_transaction_amount = 150;

    blockchain = create_blockchain(senders5, receivers5, amounts5, transactions, transactions_per_block, max_transaction_amount);
    assert(blockchain->size == 1);
    assert(blockchain->transactions_per_block == 2);
    assert(blockchain->max_transaction_amount == 150);

    assert(blockchain->blocks->size == 2);
    assert(blockchain->blocks->amount == 4);

    assert(blockchain->blocks->transactions[0].id == 0);
    assert(blockchain->blocks->transactions[0].amount == 0);
    assert(strcmp(blockchain->blocks->transactions[0].sender, "A") == 0);
    assert(strcmp(blockchain->blocks->transactions[0].receiver, "D") == 0);


    assert(blockchain->blocks->transactions[1].id == 1);
    assert(blockchain->blocks->transactions[1].amount == 4);
    assert(strcmp(blockchain->blocks->transactions[1].sender, "B") == 0);
    assert(strcmp(blockchain->blocks->transactions[1].receiver, "E") == 0);

    free_blockchain(blockchain);

    puts("OK!");
    return 0;
}
