
typedef enum
  {
    CKP,
    WAIT,
    MED,
    OK,
    KO
  } OPcode;


typedef struct
{
  char hauteur[60];
  char longueur[60];
  char latitude[60];
  int photo;
  int ID;
} Checkpoints;


typedef struct
{
  int nbckp;
  Checkpoints points;
  int ID;
  int datalen;
  unsigned char data[8192];
  OPcode code;
} Packet;
