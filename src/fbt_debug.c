/**
 * @file fbt_debug.c
 * This handles the debug output that can be customized in the Makefile
 *
 * Copyright (c) 2011 ETH Zurich
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 * $Date: 2012-01-19 20:17:12 +0100 (Thu, 19 Jan 2012) $
 * $LastChangedDate: 2012-01-19 20:17:12 +0100 (Thu, 19 Jan 2012) $
 * $LastChangedBy: kravinae $
 * $Revision: 1195 $
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */
#ifdef DEBUG

#include <asm-generic/fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fbt_debug.h"
#include "fbt_code_cache.h"
#include "fbt_datatypes.h"
#include "fbt_translate.h"
#include "generic/fbt_libc.h"
#include "generic/fbt_llio.h"
#if defined(__i386__)
# include "ia32/fbt_x86_opcode.h"
#elif defined(__arm__)
# include "arm/fbt_arm_opcode.h"
#endif

/* size of buffer for memory dumps into text files */
#define PRINT__BUF__SIZE 512

/**
 * The global vars needed for debugging
 */
static pthread_mutex_t debug_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_key_t thread_debug;
int debugStream = 0;

/** This variable keeps track of how many threads are still using the
debugStream so it will not be closed before the last thread exits */
static long stream_references = 0;

/* local functions */
static char scan_half_byte(unsigned char hb);

void debug_start()
{
  pthread_mutex_lock(&debug_mutex);

  if (debugStream == 0) {
    fbt_open(DEBUG_FILE_NAME,
             O_CREAT | O_TRUNC | O_WRONLY,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |  \
             S_IWOTH, debugStream);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
      debugStream, "Could not open debug file (debug_start: fbt_debug.c).\n");
  }
  fllprintf(debugStream, "Start debugging\n\n");
  if (pthread_key_create(&thread_debug, NULL) != 0) {
    fbt_suicide_str("Error creating thread local\n");
  }
  pthread_setspecific(thread_debug, (void *)0);

  stream_references += 1;

  pthread_mutex_unlock(&debug_mutex);
}

void debug_end()
{
  pthread_mutex_lock(&debug_mutex);

  stream_references -= 1;
  if (stream_references < 0) {
    fbt_suicide_str("Unbalanced debug_start / debug_end.\n");
  }

  int destroy = stream_references == 0;
  int old_debug_stream = debugStream;

  if (destroy) {
    debugStream = 0;
  }

  pthread_mutex_unlock(&debug_mutex);

  if (destroy) {
    //pthread_mutex_destroy(&debug_mutex);
    fllprintf(old_debug_stream, "\nStop debugging\n");
    int ret;
    fbt_close(old_debug_stream, ret);
    SYSCALL_SUCCESS_OR_SUICIDE_STR(
        ret, "BT failed to close debug file (debug_end: fbt_debug.c)\n");
    pthread_key_delete(thread_debug);
  }
}

void debug_print_function_start(char *str, ...)
{
  pthread_mutex_lock(&debug_mutex);

  if (debugStream == 0) {
    fbt_suicide_str("Debug stream is not open.\n");
  }

  va_list ap;
  va_start(ap, str);

  long i, n = (long)pthread_getspecific(thread_debug);
  for (i = 0; i < n; i++) {
    fllprintf(debugStream, "\t");
  }
  fllprintfva(debugStream, str, ap);
  va_end(ap);
  for (i = 0; i < n; i++) {
    fllprintf(debugStream, "\t");
  }
  fllprintf(debugStream, "{\n");
  n++;
  /*fflush(debugStream);*/
  pthread_setspecific(thread_debug, (void *)n);
  pthread_mutex_unlock(&debug_mutex);
}

void debug_print_function_end(char *str, ...)
{
  if (debugStream == 0) {
    fbt_suicide_str("Debug stream is not open.\n");
  }

  va_list ap;
  va_start(ap, str);
  pthread_mutex_lock(&debug_mutex);
  long i, n = (long)pthread_getspecific(thread_debug);
  n--;
  for (i = 0; i < n; i++) {
    fllprintf(debugStream, "\t");
  }
  fllprintf(debugStream, "}");
  fllprintfva(debugStream, str, ap);
  va_end(ap);
  fllprintf(debugStream, "\n");
  if (n == 0) fllprintf(debugStream, "\n");
  /*fsync(debugStream);*/
  pthread_setspecific(thread_debug, (void *)n);
  pthread_mutex_unlock(&debug_mutex);
}

void debug_print(char *str, ...)
{
  pthread_mutex_lock(&debug_mutex);

  if (debugStream == 0) {
    fbt_suicide_str("Debug stream is not open.\n");
  }

  va_list ap;
  va_start(ap, str);
  long i, n = (long)pthread_getspecific(thread_debug);

  for (i = 0; i < n; i++) {
    fllprintf(debugStream, "\t");
  }

  fllprintfva(debugStream, str, ap);
  fllprintf(debugStream, "\n");
  /*fflush(debugStream);*/
  pthread_mutex_unlock(&debug_mutex);
}

static char scan_half_byte(unsigned char hb)
{
  switch (hb & 0x0f) {
  case 10:
    return 'a';
  case 11:
    return 'b';
  case 12:
    return 'c';
  case 13:
    return 'd';
  case 14:
    return 'e';
  case 15:
    return 'f';
  }
  return hb + '0';
}

char* debug_memdump(unsigned char *addr, unsigned int n)
{
  static char print_buf[PRINT__BUF__SIZE];
  unsigned int i;
  for (i=0; i<n && i<(PRINT__BUF__SIZE-1)/2; ++i) {
    print_buf[2*i] = scan_half_byte(addr[i] >> 4);
    print_buf[2*i+1] = scan_half_byte(addr[i] & 0x0f);
  }
  print_buf[2*i] = '\0';
  return print_buf;
}

#endif  /* DEBUG */
