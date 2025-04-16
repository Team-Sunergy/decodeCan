#include "./include/HT.h"
#include "./include/can.h"

#define INACTIVE    0
#define ACTIVE      1


typedef struct decoder {
    HashTable decoderHashTable;
    bool state;
} decoder;

/**
 * Initializes the decoder.
*/
void init_decoder(*decoder currentDecoder) {
    bool currentDecoder->state = 0; // inactive state
    
}
