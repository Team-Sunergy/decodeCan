
#define MAXSIZE 0xFFF    // this is the size of hashtable.
                        // the size only needs to be size of the
                        // num of different ids we have but FFF works

typedef struct item {
    int32_t key;    // key to input to obtain value
    int32_t value;  // value for key
} item;

typedef struct HashTable
{
    item items[MAXSIZE];           // items 
    int32_t count;                 // count of items
    int32_t size;                  // size of tables
    LinkedList* overflowBucket;   // overflow

} HashTable;


