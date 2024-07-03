#ifndef PNG_ENCODER_H
#define PNG_ENCODER_H

typedef unsigned char u8;
typedef struct PNGEncoder_t {
    u8* buffer;
} PNGEncoder;

void read_buffer(PNGEncoder p);

#endif