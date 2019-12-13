#include <stdio.h>
#include <string.h>
#include "fuzz_util.h"

#define UNUSED(X) (void)X

static char *m_fuzz_input_data; /* Mock data*/
static ssize_t m_remaining; /* Remaining bytes in mocked data socket */
static ssize_t m_idx;    /* Index of next read in mock data */

void fuzz_set_input(char *data, ssize_t len) {
  m_fuzz_input_data = data;
  m_remaining = len;
  m_idx = 0;
}

ssize_t	fuzz_read_socket(int dummy_socket, void *buf, size_t bcount) {
  UNUSED(dummy_socket);
  if (bcount > m_remaining) {
    bcount = m_remaining;
  }
  if (0 == m_remaining) {
    /* HTTP Client has delivered request and closes socket, giving -1 error
    (EOF is signalled by returning 0 and can never happen in the scenario) */
    return -1;
  }
  memcpy(buf, m_fuzz_input_data + m_idx, m_remaining);
  m_remaining -= bcount;
  m_idx += bcount;
  /* We read X bytes and HTTP client still has socket open*/
  return bcount;
}