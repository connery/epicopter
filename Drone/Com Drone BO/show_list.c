#include <stdio.h>

#include "node.h"

void show(node *head) {
  node *current = head;

  while (current != NULL) {
    printf("Current = %i", current->p.ID);

    if (current->prev != NULL)
      printf(" Prev = %i", current->prev->p.ID);
    else
      printf(" Prev = NULL");

    if (current->next != NULL)
      printf(" Next = %i\n", current->next->p.ID);
    else
      printf(" Next = NULL\n");

    current = current->next;
  }
}
