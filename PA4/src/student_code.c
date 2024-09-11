#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "student_code.h"

int statusno, _initialized;

node_t *_chunklist;
void *_arena_start, *_arena_end;


void print_header(node_t *header){
  //Note: These printf statements may produce a segmentation fault if the buff
  //pointer is incorrect, e.g., if buff points to the start of the arena.
  printf("Header->size: %lu\n", header->size);
  printf("Header->fwd: %p\n", header->fwd);
  printf("Header->bwd: %p\n", header->bwd);
  printf("Header->is_free: %d\n", header->is_free);
}


int init(size_t size) {
  if(size > (size_t) MAX_ARENA_SIZE) {
    return ERR_BAD_ARGUMENTS;
  }


  // Find pagesize and increase allocation to match some multiple a page size
  // Question: Why is it good to match our allocation to the size of the page?
  int pagesize = getpagesize();

  if (pagesize <= 0)
    return ERR_CALL_FAILED;

  //Align to page size
  if( size % pagesize != 0 ) {
    // Calculate how much we need to increase to match the size of a page
    size -= size % pagesize;
    size += pagesize;
  }

  // Open up /dev/zero to zero-init our memory.
  int fd=open("/dev/zero",O_RDWR);
  if (fd == -1) {
    return ERR_SYSCALL_FAILED;
  }
  // Map memory from /dev/zero using mmap()
  _arena_start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  if (_arena_start == MAP_FAILED) {
    return ERR_SYSCALL_FAILED;
  }

  _arena_end = _arena_start + size;
  _initialized = 1;

  _chunklist = _arena_start;
  _chunklist -> size = size - sizeof(node_t);

  //  mmap sets the initial memory value
  // to zero so the fwd pointer of the is already null, but
  // it doesn't hurt to make that clear
  _chunklist -> fwd = NULL;
  _chunklist -> bwd = NULL;
  _chunklist -> is_free = true;

   return size;
}

int destroy() {

  if (_initialized == 0) {
    return ERR_UNINITIALIZED; 
  }

  // Remove arena with munmap()
  if(munmap(_arena_start, _arena_end - _arena_start) == -1) {
    return ERR_SYSCALL_FAILED;
  }

  // Question: Are there memory leaks here?

  // Clean up variables
  _arena_start = NULL;
  _arena_end = NULL;
  _chunklist = NULL;
  _initialized = 0;

  return 0;
}


node_t * find_first_free_chunk(size_t size, node_t* starting_node) {
  // todo
  
   node_t *current_node = starting_node;
    
    while (current_node != NULL) {
        if (current_node->is_free && current_node->size >= size) {
            return current_node;
        } else if (current_node->fwd != starting_node && current_node->fwd != NULL) {
            current_node = current_node->fwd;
	} else {
            return NULL;
	    break;
	}
    }
    
    return NULL; 
}

void split_node(node_t* node, size_t size) {

  if (node->size == size){
    // Then the node is exactly the right size
    // todo
    //
    // I am missing something here. 
    node->is_free = false;
    return;
  } else if(node->size - size < sizeof(node_t)){
    // Then the node is bigger than requested, but too small to split
    // todo
    node->is_free = false;
    return;
  } else {
    // If the requested memory does not take up the entire free chunk, we need to
    // to split that chunk and add a new node to the free list.

    // todo
    
    node_t* next = (void*)node + size + sizeof(node_t); 
    next->size = node->size - size - sizeof(node_t);  
    next->is_free = true; 

    next->fwd = node->fwd;
    if (next->fwd != NULL) {
        next->fwd->bwd = next;
    }
    next->bwd = node;
    node->fwd = next; 

    node->size = size; 
    node->is_free = false; 
      
    if (next->fwd != NULL) {
        next->fwd->bwd = next; 
    }
    
    /*  ---------- Previous Attempt ------------
    next = (node_t*)node + node->size;

    node->size -= (size + sizeof(node_t));

    next->size = size;
    next->is_free = true;
    next->fwd = node->fwd;
    next->bwd = node;
    ----------------------------------------- */
  }

  // Update header to correct size and state
  // todo
}

node_t* get_header(void* ptr) { 
  // todo
  //node_t* header = (node_t*) ptr - sizeof(node_t);  // textbook has ptr - 1
  node_t* header = (node_t*)((char*)ptr - sizeof(node_t));
  return header;
}

void coalesce_nodes(node_t* front, node_t* back) {
  if (front > back) {
    // Check to make sure they're in the right order
    // todo 
  
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if (front == back) {
    // Check to make sure they aren't the same node
    // todo
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if (front == NULL || back == NULL) {
    // Then one of them is already the end of the list
    // todo
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if ( ! (front->is_free && back->is_free)) {
    // Then one of them isn't free
    // todo
    statusno = ERR_CALL_FAILED;
    return;
  }
  // We want to do two things: skip over the second node and update size.
  // todo
  front->size += (back->size + sizeof(node_t)); 
  back->size = 0;
  front->fwd = back->fwd;
  if (front->fwd != NULL) {
    front->fwd->bwd = front;
  }
}


void* mem_alloc(size_t size){

  // Check to make sure we are initialized, and if not set statusno and return NULL;
  if(_initialized == 0) {
    // todo
    statusno = ERR_UNINITIALIZED; 
    return NULL;
  }

  // Find a free chunk of memory
  //node_t* node = NULL; // todo
  node_t* node = find_first_free_chunk(size, _chunklist);

  // If finding a node returned NULL then we're out of memory
  if (node == NULL) {
    // todo
    statusno = ERR_OUT_OF_MEMORY;
    return NULL;
  }

  // Split node to be the appropriate size, since there's no guarantee a free node is the right size already
  // todo
  split_node(node, size);

  //todo: fix this return to point at the memory we just allocated

  return ((void*)node) + sizeof(node_t);
}

void mem_free(void *ptr){

  if (ptr == NULL){
    return;
  }

  if (ptr < _arena_start || ptr > _arena_end){
    // Then the pointer is outside of the arena
    // todo
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }

  // Step backward from the pointer to look at the node header
  // todo
  node_t* header = (node_t*)((void*)ptr - sizeof(node_t));

  // Free the memory
  // todo
  header->is_free = true;

  // Coalesce together the chunks
  // todo
  if (header->bwd != NULL) {
    node_t* front = header->bwd;
    coalesce_nodes(front, header);
  }

  if (header->fwd != NULL) {
    node_t* back = header->fwd;
    coalesce_nodes(header, back);
  }

  if (header->fwd == NULL && header->bwd == NULL) {
    header->size = getpagesize() - sizeof(node_t);
  }

}


