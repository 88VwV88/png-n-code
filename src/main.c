#include "PNGdCoder.h"
#include <corecrt.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *fp = fopen("mandel.png", "rb");

  fseek(fp, 0, SEEK_END);
  size_t buf_size = ftell(fp);
  rewind(fp);

  char buffer[buf_size + 1];
  buffer[buf_size] = '\0';

  int i = 0;
  while (!feof(fp))
    buffer[i++] = fgetc(fp);

  printf("status code: %d\n",
         read_png_data((u8 *)buffer, NULL, strlen(buffer)));

  return 0;
}