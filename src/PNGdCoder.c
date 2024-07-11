#include "lodepng.h"
#include "zlib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* error codes */
const errno_t OK = 0;
const errno_t ANC_CHUNK = 1;
const errno_t INVALID_BUFFER = 2;
const errno_t UNKNOWN_CHUNK = 3;
const errno_t MEM_ERROR = 4;
const size_t MIN_BUFFER_SIZE = 56;
/* PNG codes */
const unsigned PNG_HEAD[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
/* type definitions */
typedef uint8_t u8;
typedef uint32_t u32;
typedef _Bool bool;
typedef struct IHDR_t {
  u32 width;
  u32 height;
  u8 depth;
  u8 color_type;
  bool interlace;
  u32 CRC;
} IHDR;
typedef struct IDAT_t {
  u32 length;
  u8 *data;
  u32 CRC;
} IDAT;

u32 bytes_to_uint(u8 *bytes, size_t size) {
  u32 value = 0;
  for (u32 i = 0, f = 1; i < size; ++i, f *= 256)
    value += f * bytes[size - i - 1];

  return value;
}

void print_bytes(u8 *bytes, size_t size) {
  if (bytes == NULL)
    printf("cannot print NULL bytes\n");

  printf("[ ");
  for (unsigned i = 0; i < size; ++i)
    printf("%2.2X ", bytes[i]);
  printf("]\n");
}

size_t file_size(FILE *restrict fp) {
  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  rewind(fp);

  return size;
}

u32 read_u32(u8 **pBuf, size_t size) {
  u8 bytes[size];
  memset(bytes, 0, size);

  memcpy(bytes, *pBuf, size);
  *pBuf += size;
  return bytes_to_uint(bytes, size);
}

errno_t read_png_data(u8 *buffer, void **chunks, const size_t size) {
  buffer += 8;

  IHDR *ihdr = malloc(sizeof(IHDR));

  print_bytes(buffer, 4);
  if (read_u32(&buffer, 4) != 13) {
    free(ihdr);
    return INVALID_BUFFER;
  }

  print_bytes((u8 *)buffer, 4);
  buffer += 4;

  ihdr->width  = read_u32(&buffer, 4);
  ihdr->height = read_u32(&buffer, 4);
  ihdr->depth  = read_u32(&buffer, 1);
  ihdr->color_type = read_u32(&buffer, 1);

  if (read_u32(&buffer, 2) != 0) {
    free(ihdr);
    return INVALID_BUFFER;
  }

  ihdr->interlace = read_u32(&buffer, 1);
  ihdr->CRC = read_u32(&buffer, 4);

  printf("IHDR: {\n"
         "\twidth: %d\n"
         "\theight: %d\n"
         "\tdepth: %d\n"
         "\tcolor_type: %d\n"
         "\tinterlace: %d\n}\n",
         ihdr->width, ihdr->height, ihdr->depth, ihdr->color_type,
         ihdr->interlace);

  IDAT *idat = malloc(sizeof(IDAT));
  idat->length = read_u32(&buffer, 4);
  buffer += 4; // IDAT chunk name

  idat->data = malloc(sizeof(u8) * idat->length);


  u8* data = malloc(sizeof(u8) * idat->length);
  memcpy(data, buffer, idat->length);
  buffer += idat->length + 4;
  idat->CRC = read_u32(&buffer, 4);

  unsigned long length;
  const u32 error = uncompress(idat->data, &length, data, idat->length);

  if (error != Z_OK)
    printf("uncompress successful!\n");
  else
    printf("uncompress unsuccessful: %d\n", error);

  printf("IDAT: {\n"
         "\tlength: %d\n\tdata: ", idat->length);
  print_bytes(idat->data, idat->length);
  printf("}\n");

  return OK;
}
