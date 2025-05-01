#include <cstdint>
#include <cstdio>
#include "../include/HT.h"
#include "../include/can.h"
#include "../include/decoder.h"
#include "../include/parseMessage.h"
/**
 * Initializes the decoder.
*/
void init_decoder(decoder* currentDecoder) {
    currentDecoder->state = 0;                                  // inactive state
    currentDecoder->decoderHashTable = create_table(NUM_IDS);   // create table size num ids
}

/**
 * Starts decoding process
*/
void start_decoder(decoder* currentDecoder) {
    currentDecoder->state = ACTIVE;  // active state
}

/**
 * Updates value in decoder. id is id to update with value
*/
void update_decoder(decoder* currentDecoder, int id, int message) {
    if(currentDecoder->state == INACTIVE) {
        printf("decoder is stopped, start decoder to update\n");
        return;
    }
    // parse message code
    // psuedo code to parse
    parseMessage(currentDecoder, BMS_ID, message);
}

int grab_field(decoder* currentDecoder, int field) {
    
    int* val;
    // search for item
    if((val = ht_search(currentDecoder->decoderHashTable, field)) == NULL) {
        printf("value has not been updated\n");
        return -1; 
    }

    return *val;
}

/**
* temp stops decoder table
*/
void stop_decoder(decoder* currentDecoder) {
    currentDecoder->state = INACTIVE;                    // inactive state
}

/**
* frees table
*/
void uninit_decoder(decoder* currentDecoder) {
    currentDecoder->state = INACTIVE;                    // inactive state
    free_table(currentDecoder->decoderHashTable); // free table
}