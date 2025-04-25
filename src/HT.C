#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/HT.h"


/**
 * This hash function is from 
 * https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
 * on stackoverflow :3s
 * It has a good distribution, and is very effiecient.
*/
int hash(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    x = x % CAPACITY; // so we dont go out of bounds :)
    return x;
}


LinkedList *allocate_list()
{
    // Allocates memory for a LinkedList pointer.
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    return list;
}

LinkedList *linkedlist_insert(LinkedList *list, Ht_item *item)
{
    list->num++;

    // Inserts the item onto the LinkedList.
    if (!list)
    {
        LinkedList *head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if (list->next == NULL)
    {
        LinkedList *node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList *temp = list;

    while (temp->next->next)
    {
        temp = temp->next;
    }

    LinkedList *node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

Ht_item *linkedlist_remove(LinkedList *list)
{
    // Removes the head from the LinkedList.
    // Returns the item of the popped element.
    list->num--;
    if (!list)
        return NULL;

    if (!list->next)
        return NULL;

    LinkedList *node = list->next;
    LinkedList *temp = list;
    temp->next = NULL;
    list = node;
    Ht_item *it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(LinkedList *list)
{
    LinkedList *temp = list;
    list->num=0; // set to 0 items
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->item);
        free(temp);
    }
}

LinkedList **create_overflow_buckets(HashTable *table)
{
    // create the overflow buckets array of linked lists
    LinkedList **buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));

    for (int i = 0; i < table->size; i++) {
        buckets[i] = NULL;
    }

    return buckets;
}

void free_overflow_buckets(HashTable *table)
{
    // free all the overflow buckets
    LinkedList **buckets = table->overflow_buckets;
    for (int i = 0; i < table->size; i++) {
        free_linkedlist(buckets[i]);
    }

    free(buckets);
}

Ht_item *create_item(int key, int value)
{
    // Creates a pointer to a new HashTable item.
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = key;
    item->value = value;
    printf("value: %d\n", value);
    return item;
}

HashTable *create_table(int size) {
    // creates new hashtable!!!! hahahahahahahah
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));        // mallocs
    table->size = size;         // size is equal to size given
    table->count = 0;           // count is equal to count given
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *)); // callocs (sets to 0)

    for (int i = 0; i < table->size; i++) { // declare all items in table to null
        table->items[i] = NULL;
    }

    // creates overflow bucets for everything in table
    table->overflow_buckets = create_overflow_buckets(table);
    return table;
}

void free_item(Ht_item *item)
{
    // Frees an item.
    free(item);
}

void free_table(HashTable *table)
{
    // Frees the table.
    for (int i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];

        if (item != NULL)
            free_item(item);
    }

    // Free the overflow bucket lists and its items.
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void handle_collision(HashTable *table, unsigned long index, Ht_item *item)
{
    LinkedList *head = table->overflow_buckets[index];

    if (head == NULL)
    {
        // Creates the list.
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        table->overflow_buckets[index]->num++;
        return;
    }
    else
    {
        // Insert to the list.
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

/**
 * Inserts item in hashtable
 * 
 * 
*/
void ht_insert(HashTable *table, int key, int value) {
    //printf("create item\n");
    Ht_item *item = create_item(key, value);

    // computes the index.
    //printf("hash value\n");
    int index = hash(key);

    //printf("insert into table\n");
    Ht_item *current_item = table->items[index];


    //printf("current item\n");
    if (current_item == NULL) {             // key doesnt exist
        if (table->count == table->size) {  // TABLE FULL!!!
            printf("hash Table is full\n");
            printf("how is this even possible\n");
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    }
    else {
        // case 1 update the value
        if (current_item->key == key) {
            value = table->items[index]->value;
            return;
        }
        else {
            // case2 COLLISSION!!!!
            handle_collision(table, index, item);
            return;
        }
    }
}

/**
 * Searches a table for an item given the key
*/
int *ht_search(HashTable *table, int key)
{
    // Searches for the key in the HashTable.
    // Returns NULL if it doesn't exist.
    int index = hash(key);
    Ht_item *item = table->items[index];    // grabs item at index
    LinkedList *head = table->overflow_buckets[index];

    while (item != NULL) {         // can only be NON null item
        if (item->key == key) {  // we check if items key is the key
            return &item->value;    // yay! lets return a pointer to that value
        }

        if (head == NULL) {     // if head == null it doesnt exist, bummer
            return NULL;        
        }
        item = head->item;      // if its not null, then we have an item or items in buckets
        head = head->next;
    }

    // last case scenario
    return NULL;
}

/**
 * This function deletes an item from a hash table
 * given you supply an input key.
 * 
*/
void ht_delete(HashTable *table, int key) {

    int index = hash(key);                  // get index from key
    Ht_item *item = table->items[index];    // gets item
    LinkedList *head = table->overflow_buckets[index];  // for if item isnt add items index

    if (item == NULL) { // item doesnt exist
        return;
    }
    else
    {
        if (head == NULL && item->key == key)
        {
            // collision chain does not exist.
            table->items[index] = NULL; // set table index to nill.
            free_item(item);            // free item
            table->count--;
            return;
        }
        else if (head != NULL)
        {
            // Collision chain exists.
            if (item->key == key) {         // remove this item
                free_item(item);            // frees allocated mem 
                LinkedList *node = head;    // makes 
                head = head->next;          // moves sets new head
                node->next = NULL;          // detaches current node
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);                  // frees the node
                table->overflow_buckets[index] = head;  // set the head of the list as the new item
                return;
            }

            LinkedList *curr = head;
            LinkedList *prev = NULL;

            while (curr)
            {
                if (curr->item->key == key)
                {
                    if (prev == NULL)
                    {
                        // First element of the chain.
                        // Remove the chain.
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        // This is somewhere in the chain.
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }

                curr = curr->next;
                prev = curr;
            }
        }
    }
}

void print_search(HashTable *table, int key)
{
    int *val = ht_search(table, key);

    if (val == NULL)
    {
        printf("Dont exist lol \n");
        return;
    }
    else
    {
        printf("Key:%d, Value:%d\n", key, *(val));
    }
}

void print_table(HashTable *table) {
    printf("\nHash Table\n**********************\n");
    for (int i = 0; i < table -> size; i++) {
        if (table -> items[i]) {
            printf("Index:%d, Key:%d, Value:%d\n", i,
                table->items[i]->key,
                table->items[i]->value);
        }
    }
    printf("***********************\n\n");
}

