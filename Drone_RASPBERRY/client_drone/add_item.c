#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void add_end(node *head, Packet p) {
  node *current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = malloc(sizeof(node));
  current->next->p = p;
  current->next->prev = current;
  current->next->next = NULL;
}

void add_in_list(node *head, Packet p, int nb) {
  node *current = head;
  int it = 0;

  while (current->next != NULL &&
	 it < nb) {
    current = current->next;
    it++;
  }

  if (it == nb) {
    node * new = NULL;
    new = malloc(sizeof(node));
    new->p = p;
    new->prev = current->prev;
    new->next = current;   

    current->prev->next = new;
    current->prev = new;
  }
  else 
    add_end(head, p);
}
