#include <sys/shm.h>
#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "libswiftnav/include/libswiftnav/sbp.h"
#include "libswiftnav/include/libswiftnav/sbp_messages.h"

#include "piksi_implementation.h"

#define				SHARED_MEMORY_KEY 00045

sbp_state_t			sbp_state;

sbp_pos_llh_t			pos_llh;
sbp_baseline_ned_t		baseline_ned;
sbp_vel_ned_t			vel_ned;
sbp_dops_t			dops;
sbp_gps_time_t			gps_time;

sbp_msg_callbacks_node_t	pos_llh_node;
sbp_msg_callbacks_node_t	baseline_ned_node;
sbp_msg_callbacks_node_t	vel_ned_node;
sbp_msg_callbacks_node_t	dops_node;
sbp_msg_callbacks_node_t	gps_time_node;


void	sbp_pos_llh_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context);
void	sbp_baseline_ned_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context);
void	sbp_vel_ned_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context);
void	sbp_dops_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context);
void	sbp_gps_time_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context);

int	init();
int	show_result();
int	communication_loop(int uart0_filestream);


void	sbp_pos_llh_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context)
{
  pos_llh = *(sbp_pos_llh_t *)msg; // cast the data from the SBP message to the associated message struct type sbp_pos_llh_t
}

void	sbp_baseline_ned_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context)
{
  baseline_ned = *(sbp_baseline_ned_t *)msg;
}

void	sbp_vel_ned_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context)
{
  vel_ned = *(sbp_vel_ned_t *)msg;
}

void	sbp_dops_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context)
{
  dops = *(sbp_dops_t *)msg;
}

void	sbp_gps_time_callback(uint16_t sender_id, uint8_t len, uint8_t msg[], void *context)
{
  gps_time = *(sbp_gps_time_t *)msg;
}

int	init()
{
  sbp_state_init(&sbp_state); // s->state = WAITING;

  sbp_register_callback(&sbp_state, SBP_GPS_TIME, &sbp_gps_time_callback, NULL, &gps_time_node); // sbp_pos_llh_callback association
  sbp_register_callback(&sbp_state, SBP_POS_LLH, &sbp_pos_llh_callback, NULL, &pos_llh_node);
  sbp_register_callback(&sbp_state, SBP_BASELINE_NED, &sbp_baseline_ned_callback, NULL, &baseline_ned_node);
  sbp_register_callback(&sbp_state, SBP_VEL_NED, &sbp_vel_ned_callback, NULL, &vel_ned_node);
  sbp_register_callback(&sbp_state, SBP_DOPS, &sbp_dops_callback, NULL, &dops_node);
  

  return (0);
}

int	write_result_on_shared_memory()
{
  int	shared_memory_segment_id;

  void		* shared_memory;
  sbp_pos_llh_t	* data = malloc(sizeof(data));

  if ((shared_memory_segment_id = shmget(SHARED_MEMORY_KEY, sizeof(data), 0666 | IPC_CREAT)) < 0) { /* ERROR EXIT */ }
  if ((shared_memory = shmat(shared_memory_segment_id, NULL, 0)) == (void*)(-1)) { /* ERROR EXIT */ }

  data->lat = pos_llh.lat;
  data->lon = pos_llh.lon;
  data->height = pos_llh.height;
  data->n_sats = pos_llh.n_sats;

  memcpy(shared_memory, (void *)data, sizeof(data));

  // shmdt(shared_memory); // DESTRUCTION DE LA MEMOIRE PARTAGEE

  return (0);
}

int	show_result()
{
  int	str_i;
  char	str[1000];
  char	rj[30];

  str_i = 0;

  str_i += sprintf(str + str_i, "\n\n\n\n");
  
  /* Print GPS time. */
  str_i += sprintf(str + str_i, "GPS Time:\n");
  str_i += sprintf(str + str_i, "\tWeek\t\t: %6d\n", (int)gps_time.wn);
  sprintf(rj, "%6.2f", ((float)gps_time.tow)/1e3);
  str_i += sprintf(str + str_i, "\tSeconds\t\t: %9s\n", rj);
  str_i += sprintf(str + str_i, "\n");
  
  /* Print absolute position. */
  str_i += sprintf(str + str_i, "Absolute Position:\n");
  sprintf(rj, "%4.10lf", pos_llh.lat);
  str_i += sprintf(str + str_i, "\tLatitude\t: %17s\n", rj);
  sprintf(rj, "%4.10lf", pos_llh.lon);
  str_i += sprintf(str + str_i, "\tLongitude\t: %17s\n", rj);
  sprintf(rj, "%4.10lf", pos_llh.height);
  str_i += sprintf(str + str_i, "\tHeight\t\t: %17s\n", rj);
  str_i += sprintf(str + str_i, "\tSatellites\t:     %02d\n", pos_llh.n_sats);
  str_i += sprintf(str + str_i, "\n");
  
  /* Print NED (North/East/Down) baseline (position vector from base to rover). */
  str_i += sprintf(str + str_i, "Baseline (mm):\n");
  str_i += sprintf(str + str_i, "\tNorth\t\t: %6d\n", (int)baseline_ned.n);
  str_i += sprintf(str + str_i, "\tEast\t\t: %6d\n", (int)baseline_ned.e);
  str_i += sprintf(str + str_i, "\tDown\t\t: %6d\n", (int)baseline_ned.d);
  str_i += sprintf(str + str_i, "\n");
  
  /* Print NED velocity. */
  str_i += sprintf(str + str_i, "Velocity (mm/s):\n");
  str_i += sprintf(str + str_i, "\tNorth\t\t: %6d\n", (int)vel_ned.n);
  str_i += sprintf(str + str_i, "\tEast\t\t: %6d\n", (int)vel_ned.e);
  str_i += sprintf(str + str_i, "\tDown\t\t: %6d\n", (int)vel_ned.d);
  str_i += sprintf(str + str_i, "\n");

  /* Print Dilution of Precision metrics. */
  str_i += sprintf(str + str_i, "Dilution of Precision:\n");
  sprintf(rj, "%4.2f", ((float)dops.gdop/100));
  str_i += sprintf(str + str_i, "\tGDOP\t\t: %7s\n", rj);
  sprintf(rj, "%4.2f", ((float)dops.hdop/100));
  str_i += sprintf(str + str_i, "\tHDOP\t\t: %7s\n", rj);
  sprintf(rj, "%4.2f", ((float)dops.pdop/100));
  str_i += sprintf(str + str_i, "\tPDOP\t\t: %7s\n", rj);
  sprintf(rj, "%4.2f", ((float)dops.tdop/100));
  str_i += sprintf(str + str_i, "\tTDOP\t\t: %7s\n", rj);
  sprintf(rj, "%4.2f", ((float)dops.vdop/100));
  str_i += sprintf(str + str_i, "\tVDOP\t\t: %7s\n", rj);
  str_i += sprintf(str + str_i, "\n");

  usleep(2000);

  printf(str);

  return (0);
}

int	communication_loop(int uart0_filestream)
{
	int rx_length = 0;

	unsigned char rx_buffer[2];

  if (uart0_filestream != -1)
    {
      rx_length = read(uart0_filestream, (void*)rx_buffer, 2);

      if (rx_length < 0)
	{
	  write(2, "read_error\n", 11);
	  return (-1);
	}

      fifo_write(rx_buffer[0]);
      fifo_write(rx_buffer[1]);

      if (rx_length > 0)
	{     
	  s8 ret = sbp_process(&sbp_state, &fifo_read);

	  show_result();
	}
    }

  communication_loop(uart0_filestream);

  return (0);
}

int	main(int argc, char ** argv)
{
	int uart0_filestream = -1;

	struct termios options;

  uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);

  if (uart0_filestream == -1)
    {
      write(2, "open_error\n", 11);
      return (-1);
    }

  tcgetattr(uart0_filestream, &options);
  
  options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;

  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);

  init();
  communication_loop(uart0_filestream);

  close(uart0_filestream);

  return (0);
}
