#ifndef PNGDCODER_H
#define PNGDCODER_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0;
#define INVALID_BUFFER 1;
#define UNKNOWN_CHUNK 2;

typedef unsigned char u8;
typedef enum ChunkType {
  /**
   *first chunk of PNG file: {
   * :width(4B),
   * :height(4B),
   * :bit-depth(1B): [1, 2, 4, 8, 16] (no. of bits per sample/palette index),
   * :color-type(1B): [0, 2, 3, 4, 16],
   * :compression-method(1B): [0],
   * :filter-method(1B): [0],
   * :interlace-method(1B): [0 | "no-interlace", 1 | "Adam7 interlace" ]
   * Total 13 Bytes
   */
  IHDR,
  /** contains the palette
   * [list of colors]
   */
  PLTE,
  /**
   * image data chunk, can be split among many IDAT chunks,
   * whick slightly increases filesize but allows streaming of the PNG
   */
  IDAT,
  /** marks the image end; 0 bytes in IEND ChunkData::buffer
   */
  IEND
} Chunk_t;

typedef struct ChunkData {
  int length;   /* Length of the ChunkData (4 Bytes) */
  Chunk_t type; /* Type of the Chunk (4 Bytes) */
  u8 *buffer;   /* The Chunk Data (`Length` Bytes) */
  int CRC;      /* The Cyclic Redundancy Checksum (4 bytes) */
} ChunkData_t;

/**
 * read the png file data as a string buffer.
 * @param buffer the pointer to the start of the file contents buffer.
 * @return an array of `ChunkData` with the various chunks,
   in the parsed contents or NULL if an error occurred.
 */
ChunkData_t **read_png_data(const char *__buffer);
/**
 * read the png data from file `filename`,
 * or file handle `fileptr` if `filename` is `NULL.
 * @param `filename` the name of the file to read from.
 * @param `fileptr` the FILE handle to read contents from.
 * @return an array of `ChunkData` with the various chunks,
   in the parsed contents or NULL if an error occurred.
 */
ChunkData_t **read_png_file_data(const char *__filename, FILE *__fileptr);
/**
 * parse the chunk data from a string buffer,
 * and store the chunk info and data in `chunk`.
 * @param `buffer` the string buffer to read the chunk bytes from.
 * @param `chunk` the `ChunkData_t` to return the data in.
 * @return the error code if any.
 */
int parse_chunk(char *__buffer, ChunkData_t *__chunk);

#endif