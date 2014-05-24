#ifndef __NETWORK_H__
#define __NETWORK_H__
 
#ifdef __cplusplus
extern "C" {
#endif

  typedef struct Network 
  {
    char *buffer;
    int actual;

    char*(*getBuffer)(struct Network *this);
    void(*setBuffer)(struct Network *this, char * tmp);
    int(*getActual)(struct Network *this);
    void(*incActual)(struct Network *this);
    void(*decActual)(struct Network *this);

    void(*free)(struct Network* this);
  } Network;
  
  Network  createNetwork(void); 
  void freeNetwork(struct Network* this); 

  char *getBuffer(Network *this);
  void setBuffer(Network *this, char *tmp);
  int getActual(Network *this);
  void incActual(Network *this);
  void decActual(Network *this);

#ifdef __cplusplus
}
#endif
 
#endif



