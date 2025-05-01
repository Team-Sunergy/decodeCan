#include <stdio.h>
#include <stdint.h>

#include "../include/can.h"
#include "../include/HT.h"
#include "../include/decoder.h"
#include "../include/parseMessage.h"

// we will parse through each message and use the getBits function to correctly select the bits
int getBits(int source, int low, int high)
{
   if (low < 0 || low > 63 || high < 0 || high > 63 || low > high) return -1;
   source = source << (64 - high - 1);
   source = source >> ((64 - high - 1) + low);
   return source;
}

int parseMessage(decoder * currentDecoder, int id, uint64_t message) {
  switch(id) {
    case BMS_ID:
      ht_insert(currentDecoder->decoderHashTable, STATE, getBits(message, 0, 31));
      ht_insert(currentDecoder->decoderHashTable, CHARGE, getBits(message, 32, 63));
      return 1;
    case MC_ID:
      ht_insert(currentDecoder->decoderHashTable, SPEED, getBits(message, 0, 63));
      return 1;
  }
  return 0;
} 






















/**
 * 
 * This function selects bits specified between the range of low and high.
 * @return a signed 64 bit integer 
 * 
*/
int64_t getBits(uint64_t bits, int32_t low, int32_t high)
{
  if (high > 63 || low > 63 || high < 0 || low < 0 || low > high) { 
    return 0;                           // error checking
  }
  bits = bits << (63 - high);           // remove left
  bits = bits >> ((63 - high) + low);   // remove right
  return bits;
}


