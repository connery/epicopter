#define PACKET_SIZE 4096
#define HEADER_SIZE sizeof(Header)
#define MAX_DATA PACKET_SIZE-HEADER_SIZE
 
typedef struct
{
  char is_data;   // 1 if this is a data packet, 0 for an ack
  int fragment;   // fragment number (zero indexed)
  char last;      // 1 if this is the last packet in the message, 0 otherwise
  int datalen;    // length of data in bytes - only used for last packet
} Header;

typedef struct
{
      Header header;  // the packet header (described above)
      char data[MAX_DATA];    // the contents of the packet
} Packet;
