#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "network.h"

static void initNetwork(Network *this);

Network createNetwork()
{
  Network this;
  initNetwork(&this);
  this.free = freeNetwork;
  puts("Network constructed");
  return this;
}

static void initNetwork(Network *this) {
  this->buffer = malloc(1024);
  this->actual = 0;

  this->getBuffer = getBuffer;
  this->setBuffer = setBuffer;

  this->getActual = getActual;
  this->incActual = incActual;
  this->decActual = decActual;

  puts("Network initialized");
}

void clearNetwork(Network *this) {
  free(this->buffer);
  this->actual = 0;
}

char *getBuffer(Network *this) {
  return this->buffer;
}

void setBuffer(Network *this, char *tmp) {
  bzero(this->buffer, 1024);
  strncpy(this->buffer, tmp, 1024);
}

int getActual(Network *this) {
  return this->actual;
}

void incActual(Network *this) {
  this->actual++;
}

void decActual(Network *this) {
  this->actual--;

  if (this->actual < 0)
    this->actual = 0;
}

void freeNetwork(Network *this) {
  clearNetwork(this);
  puts("Network destroyed");
}
