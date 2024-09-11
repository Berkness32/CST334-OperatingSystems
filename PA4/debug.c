#include "src/student_code.h"
#include <stddef.h>
#include <criterion/criterion.h>
#include <limits.h>
#include <stdio.h>

void* get_three_nodes() {
  void *memory = malloc(3 * sizeof(node_t));
  node_t* node0;
  node_t* node1;
  node_t* node2;

  node0 = memory;
  node1 = memory + sizeof(node_t);
  node2 = memory + 2 * sizeof(node_t);

  node0->size = 0;
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = node2;
  node1->bwd = node0;

  node2->size = 0;
  node2->is_free = true;
  node2->fwd = NULL;
  node2->bwd = node1;

  return memory;
}

int main() {

  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node0->size = 0;
  node1->size = 1;
  node2->size = sizeof(node_t) + 1;

  node_t* chunk = find_first_free_chunk(1, node0);
  cr_assert(chunk == node0);
    return 0;
}
