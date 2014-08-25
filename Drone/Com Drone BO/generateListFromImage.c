#include "node.h"
#include <sys/stat.h>
#define BUFFER_SIZE 8192

node *generateListFromImage(char *file_path) {
  node * head = NULL;
  FILE *src;
  int n, it;
  int count = 0;
  int written = 0;
  unsigned char buffer[BUFFER_SIZE];


  
  head = malloc(sizeof(node));
  if (head == NULL) {
    return NULL;
  }
  
  src = fopen(file_path, "rb");
  
  if (src) {
    struct stat st;
    stat(file_path, &st);
    head->p.ID = 0;
    head->p.datalen = st.st_size;
    head->next = NULL;
    it = 1;
    //    printf("len %i, %i\n",head->p.datalen, st.st_size);
    while (!feof(src)) {
      Packet p;

      n = fread(p.data, 1, BUFFER_SIZE, src);
      count += n;

      p.ID = it;
   
      p.datalen = n;
      //printf("%s\n", buffer);
      p.code = MED;
      add_end(head, p);
  
      it++;
    }
  }
 

  fclose(src);
  return head;
}
