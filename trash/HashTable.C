#include <string.h>
#include <stdint.h>

#include "LinkedList.C"
#include "HashTable.h"

HashTable initializeHashTable() {
    HashTable newTable;         // declare the new table
    newTable.count = 0;         // initially, hashtable has 0
    newTable.size = MAXSIZE;    // size of table is maxsize
    for(int i = 0; i < MAXSIZE; i++) {
        newTable.items[i] = NULL;     // declare all items in arr empty
    }
    return newTable;
}

item createItem(int32_t key, int32_t value) {
    item newItem;           // newItem holds key and value
    newItem.key = key;      // newItems key is provided key
    newItem.value = value;  // newItems value is provided value
    return newItem;         // return
}

void insert(HashTable table, int32_t key, int32_t value) {
    item toInsert = createItem(key, value);   // create item
    int32_t index = hash(key);                // computer hash index
    item currentItem = table.items[index];    // obtain current possible item in table

    if(currentItem != NULL) {                // hashed to
        if(currentItem.key == key) {         // same item has been in table
            update(table, key, value);       // update value in table           
            return;
        }
        // else, there is a collision.
        collision(table, toInsert);          // handles collision
        return;
    }
    else {                                    // not hashed to
        if(table.count >= MAXSIZE) {          // if table is full
            printf("Error: Table full\n");    // print error msg
            return;                           // and return
        }
    }


    table.items[index] = toInsert;                  // insert item in table
    table.count++;                                  // increase count
}

void update(HashTable table, int32_t key, int32_t value) {
    item toInsert = createItem(key, value);   // create item
    int32_t index = hash(key);                // computer hash index
    table.items[index] = toInsert;            // add item to table
}


int main() {
    return 0;
}


int collision(HashTable table, int32_t key) {
    return -1;

}

LinkedList** create_overflow_buckets(HashTable* table)
{
    // Create the overflow buckets; an array of LinkedLists.
    LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

    for (int i = 0; i < table->size; i++)
        buckets[i] = NULL;

    return buckets;
}


void free_overflow_buckets(HashTable* table)
{
    // Free all the overflow bucket lists.
    LinkedList** buckets = table->overflow_buckets;

    for (int i = 0; i < table->size; i++)
        free_linkedlist(buckets[i]);

    free(buckets);
}

/**
 * This hash function is from 
 * https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
 * on stackoverflow :3s
 * It has a good distribution, and is very effiecient.
*/
uint64_t hash(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}