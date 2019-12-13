#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fuzz_util.h"
#include <unistd.h>

#define TEST_ASSERT(x)  if (!(x)) return __LINE__;

#define RUN_TEST(FUNC)   if((lineno = FUNC()) != 0 ) { \
      fprintf(stderr, "Test failed %s:%u\n", __FILE__, lineno); \
      tests_failed++; \
  }

/**
 * Test a full read of buffer
 * \returns 0 on succes, failing line no otherwise
 */
static unsigned int test_01(void) {

  char expected_answer[] = "GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.64.1\r\nAccept: */*\r\n\r\n";
  fuzz_set_input(expected_answer, sizeof(expected_answer) - 1); /* -1 exlucde terminating zero */

  char mybuf[2000];
  ssize_t end = fuzz_read_socket(42, mybuf, 2000);
  TEST_ASSERT(end == sizeof(expected_answer) - 1); /* -1 exclude string-terminating zero*/
  TEST_ASSERT(0 == memcmp(mybuf, expected_answer, end));
  TEST_ASSERT((-1 == fuzz_read_socket(42, mybuf, 2000))); /* Expect -1 to simulate http client closing socket*/
  return 0;
}

/**
 * Test partial read
 */
static unsigned int test_02(void) {

  char expected_answer_partial[] = "GE";
  char expected_answer[] = "GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.64.1\r\nAccept: */*\r\n\r\n";
  
  fuzz_set_input(expected_answer, sizeof(expected_answer) - 1); /* -1 exlucde terminating zero */

  char mybuf[2000];
  ssize_t end = fuzz_read_socket(42, mybuf, 2);
  ssize_t total_read = end;
  TEST_ASSERT(end == 2);
  if (0 != memcmp(expected_answer_partial, mybuf, 2)) {
    return __LINE__;
  }
  end = fuzz_read_socket(42, mybuf + 2, 2000-2);
  TEST_ASSERT(end == sizeof(expected_answer) - 2 - 1 ); /* -2 for first read, -1 exclude string-terminating zero*/
  total_read += end;
  TEST_ASSERT(0 == memcmp(mybuf, expected_answer, total_read));
  TEST_ASSERT(-1 == fuzz_read_socket(42, mybuf, 2000));
  return 0;
}


int main(void)
{
  int tests_failed = 0;
  unsigned int lineno;

  RUN_TEST(test_01);
  RUN_TEST(test_02);

  if(tests_failed > 0) return -1;
  return 0;
}