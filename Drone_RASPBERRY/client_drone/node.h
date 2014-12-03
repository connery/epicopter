#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 


#include "packet.h"

typedef struct node node;
struct node
{
  Packet p;
  struct node * next;
  struct node * prev;
};

typedef node* llist;
