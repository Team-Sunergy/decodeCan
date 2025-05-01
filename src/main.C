#include <stdio.h>
#include <stdint.h>
#include "../include/HT.h"
#include "../include/can.h"
#include "../include/decoder.h"




int main() {
   decoder * currentDecoder;
   init_decoder(currentDecoder);
   start_decoder(currentDecoder);
   printf("decoder state: %d\n", currentDecoder->state);
   grab_field(currentDecoder, BMS_ID);
   uint64_t val = 3124111111163;
   update_decoder(currentDecoder, BMS_ID, val);
   printf("decoder value %d\n", grab_field(currentDecoder, BMS_ID));
   print_table(currentDecoder->decoderHashTable);
}



// void update_decoder(int id, int data) {


//     return;

// }