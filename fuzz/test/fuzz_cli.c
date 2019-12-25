#include <string.h>
#include <stdio.h>
#include <stdint.h>

char *input_filename;

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "must supply 1 argument: name of input file\n");
    return -1;
  }
  input_filename = argv[1];
  char mybuf[2000];
  FILE *fp=fopen(input_filename,"r");
  ssize_t size = fread(mybuf, 1, sizeof(mybuf), fp);
  LLVMFuzzerTestOneInput(mybuf, size);
}