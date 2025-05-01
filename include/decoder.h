#define INACTIVE    0
#define ACTIVE      1


typedef struct {
    HashTable* decoderHashTable;
    bool state;
} decoder;

/**
 * Initializes the decoder.
*/
void init_decoder(decoder* currentDecoder);

/**
 * Starts decoding process
*/
void start_decoder(decoder* currentDecoder);

/**
 * Updates value in decoder. id is id to update with value
*/
void update_decoder(decoder* currentDecoder, int id, int message);
int grab_field(decoder* currentDecoder, int field);

/**
* temp stops decoder table
*/
void stop_decoder(decoder* currentDecoder);

/**
* frees table
*/
void uninit_decoder(decoder* currentDecoder);