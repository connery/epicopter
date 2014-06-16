#include <errno.h>
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
  this->buffer = malloc(BUF_SIZE);
  this->actual = 0;
  this->socket = init_connection();
  this->clients = malloc(sizeof(Client) * MAX_CLIENTS);

  this->getBuffer = getBuffer;
  this->setBuffer = setBuffer;

  this->getActual = getActual;
  this->incActual = incActual;
  this->decActual = decActual;

  this->getSocket = getSocket;
  this->setSocket = setSocket;

  this->removeClient = removeClient;
  this->getClients = getClients;
  this->readClient = readClient;
  this->writeClient = writeClient;
  
  puts("Network initialized");
}


void removeClient(Network *this, int to_remove)
{
  puts("REMOVING CLIENT");

  closesocket(this->getClients(this)[to_remove].sock);
  memmove(this->getClients(this) + to_remove,
	  this->getClients(this) + to_remove + 1,
	  (this->getActual(this) - to_remove - 1) * sizeof(Client));

  this->decActual(this);
}

int readClient(Network *this, SOCKET csock)
{
  int n = 0;
  if ((n = recv(csock, this->buffer, BUF_SIZE - 1, 0)) < 0)
    {
      perror("recv()");
      n = 0;
    }
  puts("reading :");
  puts(this->buffer);
	 
  return n;
}

void writeClient(Network *this, SOCKET csock)
{
  puts("writing :");
  puts(this->buffer);
   if (send(csock, this->buffer, strlen(this->buffer), 0) < 0)
    {
      perror("send()");
      exit(errno);
    }
}

void clearNetwork(Network *this) {
  this->buffer = NULL;
  free(this->buffer);
  this->clients = NULL;
  free(this->clients);
  this->actual = 0;
  closesocket(this->socket);
  this->socket = 0;
}

char *getBuffer(Network *this) {
  return this->buffer;
}

void setBuffer(Network *this, char *tmp) {
  if (strlen(this->buffer) > 0)
    this->buffer = NULL;
  this->buffer = malloc(strlen(tmp));
  strncpy(this->buffer, tmp, strlen(tmp));
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

SOCKET getSocket(Network *this) {
  return this->socket;
}

void setSocket(Network *this, SOCKET tmp) {
  this->socket = tmp;
}

Client *getClients(Network *this) {
  return this->clients;
}

void freeNetwork(Network *this) {
  clearNetwork(this);
  puts("Network destroyed");
}

int init_connection()
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKADDR_IN sin = { 0 };

  if (sock == INVALID_SOCKET) {
    perror("socket()");
    exit(errno);
  }

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;

  if (bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR) {
    perror("bind()");
    exit(errno);
  }

  if (listen(sock, MAX_CLIENTS) == SOCKET_ERROR) {
    perror("listen()");
    exit(errno);
  }

  return sock;
}
