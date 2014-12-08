#include <stdio.h>
#include <stdlib.h>

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

void getInfo(node *head) {
  node *current = head;
  char str[1024] = "";

  while (current != NULL) {
    strcat(str, "O");
    sprintf(str, "%s", current->p.points.latitude);
    strcat(str, ";");
    sprintf(str, "%s", current->p.points.longueur);
    strcat(str, ";");
    sprintf(str, "%s", current->p.points.hauteur);
    strcat(str, ";");
    current = current->next;
  }
  printf("%s", str);
}
