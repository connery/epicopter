#ifndef __FLIGHTPLAN_H__
#define __FLIGHTPLAN_H_

#include "server.h"

typedef struct
{
  int id;
  Checkpoint *route;
} Flightplan;

#endif
