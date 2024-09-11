#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"



bool is_entry_valid(PageTableEntry pte) {
  // todo;
  return (pte & get_mask(1<<VALID_BIT)) != 0; 
}

bool is_read_enabled(PageTableEntry pte) {
  // todo
  // Question: Implement this function.  Hint: it can take as little as 1 line.
  return (pte & get_mask(1<<READ_BIT)) != 0;
}

bool is_write_enabled(PageTableEntry pte) { 
  // todo
  return (pte & get_mask(1<<WRITE_BIT)) != 0;
}

bool is_execute_enabled(PageTableEntry pte) {
  // todo
  return (pte & get_mask(1<<EXEC_BIT)) != 0;
}


PFN find_free_page(MMU m) {
  // todo

  // ++++++++++++++++++++++ Good +++++++++++++++++++++++++++++++++++++

  for (int i = 0; i < NUM_FRAMES; i++) {

    // Whether the page is free, not necessarily valid
    if (m.page_used[i] == false) {

      // Just need to return the index
      return i;
    }
  }
}

PFN convert_PageTableEntry_to_PFN(PageTableEntry pte) {
  // todo
  // Only need to mask out the metadata bits. 

  // ++++++++++++++++++++++ Good +++++++++++++++++++++++++++++++++++++

  //return (pte << NUM_METADATA_BITS);
  return (pte & (get_mask(NUM_METADATA_BITS) << (NUM_BITS_IN_BYTE*sizeof(PageTableEntry))));
}


/*
 * Page Table Functions
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VPN vpn) {
  // todo

  // ++++++++++++++++++++++ Good +++++++++++++++++++++++++++++++++++++

  return m.page_pointer[vpn];
}

PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec) {
  // todo
  PFN pfn = find_free_page(*m);

  if (can_read == true) {
    pfn = pfn | single_bit_mask(READ_BIT);
  }
  if (can_write == true) {
    pfn = pfn | single_bit_mask(WRITE_BIT);
  }
  if (can_exec == true) {
    pfn = pfn | single_bit_mask(EXEC_BIT);
  } 

  m->page_pointer[vpn] = pfn;
}


/*
 * Page Directory Functions
 */

Page* get_page(MMU m, VirtualAddress va, bool for_read, bool for_write, bool for_execute) {
  // todo
  // Textbook example:
  // VPN location = (va & get_mask(NUM_VPN_BITS)) >> NUM_OFFSET_BITS; 
  // return m.page_pointer[location];

  // ++++++++++++++++++++++ Good +++++++++++++++++++++++++++++++++++++

  VPN vpn = va & get_mask(NUM_VPN_BITS);
  OFFSET offset = vpn >> NUM_OFFSET_BITS;

  PageTableEntry pte = m.page_pointer[vpn];

  if (for_read == true) {
    pte = pte | single_bit_mask(READ_BIT);
  }
  if (for_write == true) {
    pte = pte | single_bit_mask(WRITE_BIT);
  }
  if (for_execute == true) {
    pte = pte | single_bit_mask(EXEC_BIT);
  }

  PFN pfn = convert_PageTableEntry_to_PFN(pte);

  Page *page = NULL;
  page = (Page *) (m.physical_memory + pfn + offset);
  return page;
}

char read_byte(MMU m, VirtualAddress va) {
  // todo

  // ++++++++++++++++++++++ Good +++++++++++++++++++++++++++++++++++++

  Page* page = get_page(m, va, 1, 0, 0);
  return page->data[0];
}

void write_byte(MMU m, VirtualAddress va, char val) {
  // todo

  Page* page = get_page(m, va, 0, 1, 0);
  page->data[va] = val;
}
