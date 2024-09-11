#include "src/student_code.h"
#include "unit_tests.c"
#include <stdio.h>

int main() {

  Group g = group_make_new("totally not cyborgs");
  Person p1 = person_make_new("Sam", "Ogden", 35);
  Person p2 = person_make_new("Andrew", "Human", 42);

  add_person(&g, &p1);

  int spaces = free_spaces_in_group(g);
  int ap = add_person(&g, &p2);
  //cr_assert(g.num_members == 1);
  printf("Is g.num_members equal to 1? %d %d %d\n", g.num_members, ap, spaces);
    return 0;
}
