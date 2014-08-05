#ifndef __CHECKPOINT_H__
#define __CHECKPOINT_H__

#include "server.h"

typedef struct
{
  char latitude[20];
  char longitude[20];
  char height[6];
} Checkpoint;

#endif
