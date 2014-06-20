#ifndef __NETWORK_H__
#define __NETWORK_H__
 
#ifdef __cplusplus
extern "C" {
#endif

  //#define closesocket(s) close(s)
#include <my_global.h>

#include "server.h"

  typedef struct Network 
  {
    char *buffer;
    int actual;
    SOCKET socket;
    Client *clients;
  
    int(*readClient)(struct Network *this, SOCKET csock);
    void(*writeClient)(struct Network *this, SOCKET csock);

    char*(*getBuffer)(struct Network *this);
    void(*setBuffer)(struct Network *this, char * tmp);
    int(*getActual)(struct Network *this);
    void(*incActual)(struct Network *this);
    void(*decActual)(struct Network *this);
    SOCKET(*getSocket)(struct Network *this);
    void(*setSocket)(struct Network *this, SOCKET tmp);
    Client*(*getClients)(struct Network *this);
    void(*removeClient)(struct Network *this, int to_remove);
    void(*free)(struct Network* this);
  
  } Network;
  
  Network  createNetwork(void); 
  void freeNetwork(struct Network* this); 
  
  int readClient(Network *this, SOCKET csock);
  void writeClient(Network *this, SOCKET csock);

  char *getBuffer(Network *this);
  void setBuffer(Network *this, char *tmp);
  int getActual(Network *this);
  void incActual(Network *this);
  void decActual(Network *this);
  SOCKET getSocket(Network *this);
  void setSocket(Network *this, SOCKET tmp);
  Client *getClients(Network *this);
  void removeClient(Network *this, int to_remove);
  
#ifdef __cplusplus
}
#endif
 
#endif



