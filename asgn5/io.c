#include "io.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

struct buffer {
    int fd;
    int offset;

    int num_remaining;
    uint8_t a[BUFFER_SIZE];
};

Buffer *read_open(const char *filename) {
    int openval = open(filename, O_RDONLY);
    if (openval < 0) {
        return NULL;
    }
    Buffer *b = (Buffer *) malloc(sizeof(Buffer));
    b->fd = openval;
    b->offset = 0;
    b->num_remaining = 0;

    return b;
}
void read_close(Buffer **pbuf) {
    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
    return;
}
bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0) {
            fprintf(stderr, "ERROR");
        }
        if (rc == 0) {
            return false;
        }
        buf->num_remaining = rc;
        buf->offset = 0;
    }
    *x = buf->a[buf->offset];
    buf->offset++;
    buf->num_remaining--;
    return true;
}

bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t one = 0;
    if (read_uint8(buf, &one) == false) {
        return false;
    }
    uint8_t two = 0;
    if (read_uint8(buf, &two) == false) {
        return false;
    }

    uint16_t z = two << 8;
    z = z | one;

    *x = z;
    return true;
}
bool read_uint32(Buffer *buf, uint32_t *x) {
    uint16_t one = 0;
    if (!read_uint16(buf, &one)) {
        return false;
    }
    uint16_t two = 0;
    if (!read_uint16(buf, &two)) {
        return false;
    }

    uint32_t z = two << 16;
    z = z | one;

    *x = z;
    return true;
}

Buffer *write_open(const char *filename) {
    int creatval = creat(filename, 0664);
    if (creatval < 0) {
        return NULL;
    }
    Buffer *b = (Buffer *) malloc(sizeof(Buffer));
    b->fd = creatval;
    b->offset = 0;
    b->num_remaining = 0;

    return b;
}
void write_close(Buffer **pbuf) {
    uint8_t *start = (*pbuf)->a;
    int num_bytes = (*pbuf)->offset;

    do {
        ssize_t rc = write((*pbuf)->fd, start, num_bytes);
        if (rc < 0) {
            fprintf(stderr, "ERROR\n");
        }
        start += rc;
        num_bytes -= rc;
    } while (num_bytes > 0);

    (*pbuf)->offset = 0;

    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
}
void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->a;
        int num_bytes = buf->offset;

        do {
            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0) {
                fprintf(stderr, "ERROR\n");
            }
            start += rc;
            num_bytes -= rc;
        } while (num_bytes > 0);

        buf->offset = 0;
    }
    buf->a[buf->offset] = x;
    buf->offset++;
    return;
}
void write_uint16(Buffer *buf, uint16_t x) {
    write_uint8(buf, x);
    write_uint8(buf, x >> 8);
    return;
}
void write_uint32(Buffer *buf, uint32_t x) {
    write_uint16(buf, x);
    write_uint16(buf, x >> 16);
    return;
}
