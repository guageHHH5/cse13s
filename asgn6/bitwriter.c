#include "bitwriter.h"

#include "io.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    Buffer *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *buf = calloc(1, sizeof(BitWriter));
    Buffer *underlying_stream = write_open(filename);
    if (underlying_stream == NULL) {
        fprintf(stderr, "Do later.\n");
        free(underlying_stream);
        return NULL;
    }
    buf->underlying_stream = underlying_stream;
    return buf;
}

void bit_write_close(BitWriter **pbuf) {
    if ((*pbuf)->bit_position > 0) {
        write_uint8((*pbuf)->underlying_stream, (*pbuf)->byte);
    }
    write_close(&(*pbuf)->underlying_stream);
    free(*pbuf);
    (*pbuf) = NULL;
    return;
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        write_uint8(buf->underlying_stream, buf->byte);
        buf->byte = 0x00;
        buf->bit_position = 0;
    }
    if (bit & 1) {
        buf->byte |= (bit & 1) << buf->bit_position;
    }
    ++(buf->bit_position);
    return;
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (uint8_t i = 0; i <= 15; i++) {
        uint8_t pseudo = (x >> i) & 1;
        bit_write_bit(buf, pseudo);
    }
    return;
}
void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (uint8_t i = 0; i <= 31; i++) {
        uint8_t pseudo = (x >> i) & 1;
        bit_write_bit(buf, pseudo);
    }
    return;
}
void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (uint8_t i = 0; i <= 7; i++) {
        uint8_t pseudo_byte = (byte >> i) & 1;
        bit_write_bit(buf, pseudo_byte);
    }
    return;
}
