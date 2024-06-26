/******************************************************************************
 * 
 * CS105: Cachelab
 *
 * Partner 1: Bradley Kosgei
 *
 * Partner 2: Gisele Umutoni
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "caching.h"


/******************************************************************************
 * parse_addr takes four arguments. The first argument (addr) is a (64-bit) 
 * address to parse. The other three arguments are addresses for where to 
 * write the parsed tag, index, and offset (respectively).
 *****************************************************************************/
void parse_addr(void* addr, long* tag_ptr, byte* index_ptr, byte* offset_ptr){
  
  // TODO #1: implement parse_addr
  // Hint: you might want to cast addr to an unsigned long first

  unsigned long ul_addr = (unsigned long)addr;

    *offset_ptr = ul_addr & 0xff;
    *index_ptr = (ul_addr >> 8) & 0xff;
    *tag_ptr = (ul_addr >> 16) & 0xffffffffffff;

}


/******************************************************************************
 * is_in_direct_cache takes three arguments: tag, index, and offset and
 * returns 1 if the associated address is currently stored in the cache or 
 * 0 otherwise.
 *****************************************************************************/
bool is_in_direct_cache(long tag, byte index, byte offset){
  // TODO #2: implement is_in_direct_cache

  cacheline_t line = direct_cache[index];

  return line.valid && (line.tag == tag);
}


/******************************************************************************
 * lookup_int_in_direct_cache takes three arguments: tag, index, and offset
 * and returns the integer value stored in cache at the corresponding address
 * 
 * Precondition: this function should only be called if the data at that
 * address is currently in the cache
 *****************************************************************************/
int lookup_int_in_direct_cache(long tag, byte index, byte offset){
  // TODO #3: implement lookup_int_in_direct_cache
  cacheline_t line = direct_cache [index];

  byte *val = &(line.datablock[offset]); 

  int * new_val = (int *) val;

  return * new_val;
}


/******************************************************************************
 * update_direct_cache modifies the cache by overwriting the cacheline
 * at index to respond to the cache miss for addr
 *
 * Precondition: this function should only be called if the address is NOT
 * currently in the cache
 *****************************************************************************/
void update_direct_cache(long tag, byte index, byte offset, void* addr){
  // TODO #4: implement update_direct_cache
  
  direct_cache[index].valid = 1;
  direct_cache[index].tag = tag;
  memcpy(direct_cache[index].datablock, (addr - offset), 256);
}


