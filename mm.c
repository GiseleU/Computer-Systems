/*
 * mm.c, a basic implicit list implementation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

int mm_check(void);


/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "May-Tad-Gisele",
    /* First member's full name */
    "Tadius Frank",
    /* First member's email address */
    "tcfa2018@mymail.pomona.edu",
    /* Second member's full name (leave blank if none) */
    "Gisele Umutoni",
    /* Third member's email address (leave blank if none) */
    "guaa2020@mymail.pomona.edu"
     /* Third member's full name (leave blank if none) */
    "Maymuunah Quasim",
    /* Third member's email address (leave blank if none) */
    "mmqa2020@mymail.pomona.edu"
};

#define ALIGNMENT 8
#define MIN_PAYLOAD 16

#define WORD_SIZE 8
#define CHUNK_SIZE (1 << 12)


char* base;
char* top;
char* search;  // use to implement next_fit


/*
 * Internally, all pointers are of type char*. 
 *
 * These functions are helpers for navigating block structure.
 * mostly for type casts to extract values from fields.
 *
 * They are functions rather than macros to get more secure 
 * semantics and better readability. They will be inlined by -O2.
 */


// pre-defined helper functions

// given pointer to block, return pointer to payload
char* payload_pointer(char* bp) {
  return bp + WORD_SIZE;
}

// given pointer to block, return pointer to header
size_t* header_pointer(char* bp) {
  return (size_t*)(bp);
}

// given pointer to block, return pointer to footer of prev block
char* prev_footer_pointer(char* bp) {
  return (char*)(bp - WORD_SIZE);
}

// given size of block, return size of payload
size_t payload_size(size_t blocksize) {
  return blocksize - 2 * WORD_SIZE;
}

// given size of payload, round up to multiple of alignment
size_t roundup(size_t size) { 
  return (size + ALIGNMENT - 1) & (~(ALIGNMENT - 1));
}

// given size of payload, return total size of block
size_t adjusted_size(size_t size) {
  return 2 * WORD_SIZE + ((size < MIN_PAYLOAD) ? MIN_PAYLOAD : roundup(size));
}


// TODO #1: Implement the following additional five helper functions:
// block_pointer, footer_pointer, is_allocated, block_size, and mark_block

// given pointer to payload, return pointer to start of block
char* block_pointer(void* p) {
  // Subtract 8 from p bc header is 8 bytes
  return (char*)p - WORD_SIZE;
}

// given pointer to block, return pointer to footer
size_t* footer_pointer(char* bp, size_t size) {
  // start at bp go all the way to the end by adding size and go back because the size of fp is 8
  return (size_t*) (bp + size - WORD_SIZE);
}

// given pointer to block, return allocation status
int is_allocated(char* bp) {
// get the header point and dereference it to get the value at that address and use the "and" operator to check if the last bit is one or zero.
 return *(header_pointer(bp)) & 0x1;
}

// given pointer to block, return size of block
size_t block_size(char* bp) {
// get the header point and dereference it to get the value at that address and use the "and" operator to get rid of the last bit (if the bit is one).
   return *(header_pointer(bp)) & (~0x1);
  }


// given a block pointer, a size, and an allocation status (0 or 1), set the header/footer
void mark_block(char* bp, size_t size, int allocated) {
// 
  size_t tag = size | allocated;
  *(header_pointer(bp)) = tag;
  *(footer_pointer(bp, size)) = tag;

}




// initialize heap
int mm_init(void) {
  // initialize heap with 1 block of size CHUNK_SIZE
  // (plus wiggle room for fixing the alignment
  base = (char*)mem_sbrk(CHUNK_SIZE + WORD_SIZE);
  if (base == (char*)(-1)){
    return -1;
  }

  // define correctly-aligned base and top of heap
  base = (char*)(roundup((size_t)base));
  top = base + CHUNK_SIZE;

  // initialize the one block in heap as size=CHUNCK_SIZE, currently free
  mark_block(base, CHUNK_SIZE, 0);

  // initialize search pointer to free block
  search = base;
  
  return 0;
}


// find the first block of size >= totalsize
// return top if no suchblock exists
inline char* first_fit(size_t totalsize){

  // search from beginning of heap to top
  char* p = base;
  while (p < top && (is_allocated(p) || block_size(p) < totalsize)){ // check if this is not the top of the HEAP (so there is a next) AND check if p is allocated or  
    p += block_size(p);
  }

  // if no available block, return top
  if(p >= top){
    p = top;
  }
  
  return p;
}







// find the next block of size >= totalsize (i.e., search from last allocated block)
// return top if no such block exists
inline char* next_fit(size_t totalsize){

  char* p = search;

  while (p < top && (is_allocated(p) || block_size(p) < totalsize)){ // check if this is not the top of the HEAP (so there is a next) AND check if p is allocated or  
    p += block_size(p);
  }

  // if no available block, return top
  if(p >= top){
    p = base;

    // from base to search 
    while (p < search && (is_allocated(p) || block_size(p) < totalsize)){ // check if this is not the top of the HEAP (so there is a next) AND check if p is allocated or  
      p += block_size(p);
    }

    if (p >= search){
      p = top;
    }
  }
  
  search = p;

  return p;

//// what we wrote

}


// allocate memory
void* mm_malloc(size_t size) {
  size_t totalsize = adjusted_size(size);
  size_t blocksize;
  size_t excess;
  char* p;

  if (size == 0){
    return NULL;
  }

  // search for a free block that fits this size
  // p = first_fit(totalsize); // TODO #3: switch to next_fit
  p = next_fit(totalsize); 

  // if no available block, extend heap
  if (p == top) {
    // avoid making lots of small blocks
    if(totalsize < 256){ // value 256 was determined experimentally
      excess = 256;
      blocksize = totalsize + excess;      
    } else {
      excess = 0;
      blocksize = totalsize;
    }

    // extend heap by blocksize
    mem_sbrk(blocksize);
    top += blocksize;
  } else { // compute excess space in selected block
    blocksize = block_size(p);
    excess = block_size(p) - totalsize;
  }

  // if excess isn't big enough, don't bother splitting
  if (excess <= 2 * WORD_SIZE + MIN_PAYLOAD) {
    totalsize = blocksize;
    mark_block(p, totalsize, 1); 
  } else { // split block
    mark_block(p, totalsize, 1);
    mark_block(p + totalsize, excess, 0);
  }

  return payload_pointer(p);
}


// free memory
void mm_free(void* p) {
  char* bp = block_pointer(p);
  size_t size = block_size(bp);

  //Check if there is a previous block
 int move_status = 0;
 if (bp > base){

    size_t* prev_fp = prev_footer_pointer(bp);

    size_t prev_block_size = block_size(prev_fp);

    // Check if previous block is allocated

    if (!is_allocated(prev_fp)){
      size += prev_block_size; 
      if (bp == search){
        move_status = 1;
      }
      bp -= prev_block_size;
    }
    }
  // Check if there is a next block
   if ((bp + size) < top){
    char* next_bp = bp + size;
    if (next_bp == search){
        move_status = 1;
    }
    size_t next_block_size = block_size(next_bp);

  //  Check if next block is free
    if (!(is_allocated(next_bp))){
      size += next_block_size;
    }
  }
  
  if (move_status){
    search = bp;
  } 
  // mark as un-allocated
  mark_block(bp, size, 0);
}


// ignore --- included for compatibility with test suite
void* mm_realloc(void* p, size_t newsize) {
  return NULL;
}


// helper function that checks the heap
int mm_check(void) {
  int result = 0;
  int prev_is_free = 0;
  size_t blocksize;

  // loop through all the blocks in the heap for common errors
  char* p = base;
  while (p < top) {
    // check for contiguously allocated blocks 
    if (prev_is_free && is_allocated(p)) {
      printf("contiguous allocated blocks!\n");
      result = -1;
    }

    // check that the tags match
    blocksize = block_size(p);
    if (*(size_t*)p != *(size_t*)(p + blocksize - WORD_SIZE)) {
      printf("tags differ!\n");
      result = -1;
    }
    p += blocksize;
  }

  // make sure heap ends at a block boundary
  if (p != top) {
    printf("missed the top!\n");
    result = -1;
  }
  
  return result;
}
