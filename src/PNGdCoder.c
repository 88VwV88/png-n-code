#include "PNGdCoder.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>


/* error codes */
const errno_t OK = 0;
const errno_t ANC_CHUNK = 1;
const errno_t INVALID_BUFFER = 2;
const errno_t UNKNOWN_CHUNK = 3;
const errno_t MEM_ERROR = 4;
/* PNG codes */
const unsigned PNG_HEAD = 0x89;

int sum_bytes(u8 *bytes, size_t size) {
  if (size == 0)
    return 0;

  return *bytes + sum_bytes(bytes + 1, size - 1);
}

void print_bytes(u8 *bytes, size_t size) {
  for (unsigned i = 0; i < size; ++i)
    printf("%2.2X ", bytes[i]);
  printf("\n");
}

int parse_chunk(u8 *restrict buffer, ChunkData_t *chunk) {
  u8 *read = calloc(5, sizeof(u8));
  memcpy(read, buffer, 4);

  chunk->length = sum_bytes(read, 4);

  char type[5] = "";
  memcpy(type, buffer + 4, 4);

  if (islower(type[0]))
    return ANC_CHUNK; // return for anciliary chunks (TODO)

  if (strcmp(type, "IHDR") == 0)
    chunk->type = IHDR;
  else if (strcmp(type, "PLTE") == 0)
    chunk->type = PLTE;
  else if (strcmp(type, "IDAT") == 0)
    chunk->type = IDAT;
  else if (strcmp(type, "IEND") == 0) {
    chunk->type = IEND;
    return OK;
  } else
    return UNKNOWN_CHUNK;

  printf("chunk type: %d\n", chunk->type);

  if (chunk->length != 0)
    chunk->buffer = malloc(sizeof(u8) * chunk->length);
  else
    return INVALID_BUFFER;

  memcpy(chunk->buffer, buffer + 8, chunk->length);

  return OK;
}

ChunkData_t **read_png_data(char *restrict filename) {
  FILE *fp = fopen(filename, "rb");

  u8 header[9] = "";
  fread(header, 1, 8, fp);

  printf("header data: ");
  print_bytes(header, sizeof(header));

  u8 *buffer = NULL;
  buffer = calloc(21, sizeof(u8));

  if (buffer == NULL) {
    fclose(fp);
    perror("failed to allocate buffer");
    return NULL;
  }

  ChunkData_t ihdr;

  unsigned error;
  fread(buffer, 1, 20, fp);
  if ((error = parse_chunk(buffer, &ihdr)) != OK) {
    printf("failed to parse chunk, code: %d!\n", error);
  } else {
    printf("IHDR data: ");
    print_bytes(ihdr.buffer, ihdr.length);
  }

  fclose(fp);

  return NULL;
}