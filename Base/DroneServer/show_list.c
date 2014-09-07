#include <stdio.h>

#include "node.h"

void show(node *head) {
  node *current = head;

  while (current != NULL) {
    printf("ID in list %i\n", current->p.ID);
    
    current = current->next;
  }
}
