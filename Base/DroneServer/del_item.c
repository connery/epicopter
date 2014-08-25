#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void del_end(node *head) {
  node *current = head;
  while (current->next != NULL)
    current = current->next;

  current->prev->next = NULL;
  current = NULL;
  free(current);
}

void del_in_list(node *head, int nb) {
  node *current = head;
  int it = 0;
  
  while (current->next != NULL &&
	 it < nb) {
    current = current->next;
    it++;
  }
  
  if (it == nb) {
    current->prev->next = current->next;
    current->next->prev = current->prev;
    current = NULL;
    free(current);
  }
  else
    del_end(head);

}
