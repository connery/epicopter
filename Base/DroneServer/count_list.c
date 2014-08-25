#include <stdio.h>
#include <stdlib.h>

#include "node.h"

int count_item(node *head) {
  int cb = 0;
  node *current = head;

  while (current != NULL) {
    current = current->next;
    cb++;
  }
  return cb;

  //  for (cb = 0; current != NULL; current = current->next, cb++);
  //return cb;
}
