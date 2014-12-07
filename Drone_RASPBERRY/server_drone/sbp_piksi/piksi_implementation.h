/*
 * Copyright (C) 2014 Swift Navigation Inc.
 * Contact: Colin Beighley <colin@swift-nav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * tutorial_implementation contains functions and definitions that are implementation
 * specific to this tutorial, to keep main.c as simple as possible.
 */
 
/* Epicopter 1.0 release */  

#define DO_EVERY(n, cmd) do { static u32 do_every_count = 0; if (do_every_count % (n) == 0) { cmd; } do_every_count++; } while(0)

/* FIFO functions */

u8	fifo_empty(void);
u8	fifo_full(void);
u8	fifo_write(char c);
u8	fifo_read_char(char *c);

u32	fifo_read(u8 *buff, u32 n, void *context);


/* FIFO to hold received UART bytes before libswiftnav SBP submodule parses them. */
#define FIFO_LEN 60

char	sbp_msg_fifo[FIFO_LEN];

u16	head = 0;
u16	tail = 0;

u8	fifo_empty(void) /* Return 1 if true, 0 otherwise. */
{
  if (head == tail)
    {
      return (1);
    }

  return (0);
}

u8	fifo_write(char c) /* Append a character to our SBP message fifo. Returns 1 if char successfully appended to fifo. Returns 0 if fifo is full. */
{
  if (fifo_full())
    return 0;

  sbp_msg_fifo[tail] = c;
  tail = (tail+1) % FIFO_LEN;
  return 1;
}

u8	fifo_read_char(char *c) /* Read 1 char from fifo. Returns 0 if fifo is empty, otherwise 1. */
{
  if (fifo_empty())
    {
      return (0);
    }

  *c = sbp_msg_fifo[head];
  head = (head+1) % FIFO_LEN;

  return (1);
}

u32	fifo_read(u8 *buff, u32 n, void *context) /* Read arbitrary number of chars from FIFO. Must conform to function definition that is passed to the function sbp_process(). Returns the number of characters successfully read. */
{
  int i;

  for (i = 0; i < n; i++)
    {
      if (!fifo_read_char((char *)(buff + i)))
	break;
    }

  return (i);
}

u8	fifo_full(void) /* Return 1 if true, 0 otherwise. */
{
  if (((tail + 1) % FIFO_LEN) == head)
  {
    return (1);
  }

  return (0);
}
