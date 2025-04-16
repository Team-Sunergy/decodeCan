#include "parseMessage.h"
#include <stdio.h>
#include <stdint.h>
#include <unordered_map>

// we will parse through each message and use the getBits function to correctly select the bits



























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


