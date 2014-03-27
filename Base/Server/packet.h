#define PACKET_SIZE 4096
#define HEADER_SIZE sizeof(Header)
#define MAX_DATA PACKET_SIZE-HEADER_SIZE
#define NAME_SIZE 10

typedef enum OPcode OPcode ;
enum OPcode 
  {
    NONE,
    CON,
    DEC,
    ACK,
    OK,
    KO
  };

typedef struct
{
  OPcode opcode;
  char name[NAME_SIZE];
  int datalen;
  int ID;
} Header;

typedef struct
{
      Header header;  // the packet header (described above)
      char data[MAX_DATA];    // the contents of the packet
} Packet;

