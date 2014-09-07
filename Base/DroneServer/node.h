#include "packet.h"

typedef struct node node;
struct node
{
  Packet p;
  struct node * next;
  struct node * prev;
};

typedef node* llist;
