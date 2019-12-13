#ifndef _FUZZ_UTIL_H_
#define _FUZZ_UTIL_H_
#endif

/** Read from file, maximum bcount bytes.
 * Useful for mocking out socket reads for fuzz testing.
 * \return Number of bytes read. -1 for end of data. 0 for broken pipe. In practice always -1
 */
ssize_t	fuzz_read_socket(int dummy_socket, void *buf, size_t bcount);

/**
 * Set up input data as array and length.
 */
void fuzz_set_input(char *data, ssize_t len);
