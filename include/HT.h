#define CAPACITY 2000 // Size of the HashTable.

// Defines the HashTable item.
typedef struct Ht_item
{
    int key;
    int value;
} Ht_item;

// Defines the LinkedList.
typedef struct LinkedList
{
    Ht_item *item;
    LinkedList *next;
    int num;
} LinkedList;

// Defines the HashTable.
typedef struct HashTable
{
    // Contains an array of pointers to items.
    Ht_item **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
} HashTable;


int hash(int x);
void printTableList(HashTable* list);
LinkedList *allocate_list();
LinkedList *linkedlist_insert(LinkedList *list, Ht_item *item);
Ht_item *linkedlist_remove(LinkedList *list);
void free_linkedlist(LinkedList *list);
LinkedList **create_overflow_buckets(HashTable *table);
void free_overflow_buckets(HashTable *table);
Ht_item *create_item(int key, int value);
HashTable *create_table(int size);
void free_item(Ht_item *item);
void free_table(HashTable *table);
void handle_collision(HashTable *table, unsigned long index, Ht_item *item);
void ht_insert(HashTable *table, int key, int value);
int *ht_search(HashTable *table, int key);
void ht_delete(HashTable *table, int key);
void print_search(HashTable *table, int key);
void print_table(HashTable *table);


