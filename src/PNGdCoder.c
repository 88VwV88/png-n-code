#include "PNGdCoder.h"

#include <string.h>

int parse_chunk(char *restrict buffer, ChunkData_t *chunk) {
  size_t buf_len = strlen(buffer);
  if (buf_len < 12) /* if the chunk length, type and CRC present */
    return INVALID_BUFFER;

  char *length_end = buffer + 4;
  chunk->length = strtol(buffer, &length_end, 16);

  const char type[5] = {buffer[4], buffer[5], buffer[6], buffer[7], '\0'};
  if (type[0] >= 'a' || type[0] <= 'b')
    return OK; // return for anciliary chunks (TODO)

  if (strcmp(type, "IHDR"))
    chunk->type = IHDR;
  else if (strcmp(type, "PLTE"))
    chunk->type = PLTE;
  else if (strcmp(type, "IDAT"))
    chunk->type = IDAT;
  else if (strcmp(type, "IEND"))
    chunk->type = IEND;
  else
    UNKNOWN_CHUNK;

  chunk->buffer = malloc(sizeof(u8) * chunk->length);

  if (strcpy_s((char *)chunk->buffer, chunk->length, buffer + 8) != 0)
    return INVALID_BUFFER;

  return OK;
}
