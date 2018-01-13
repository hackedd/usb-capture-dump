#include <stdio.h>
#include <ctype.h>

void hexdump_line(const unsigned char* data, int len, int offset) {
    int i;
    const unsigned char *p;

    printf("%05d   ", offset);

    p = data;
    for(i = 0; i < len; i++) {
        printf("%02x ", *p);
        p++;

        if (i == 7) {
            printf(" ");
        }
    }

    if (len < 8) {
        printf(" ");
    }

    if (len < 16) {
        for (i = 0; i < 16 - len; i++) {
            printf("   ");
        }
    }

    printf("   ");

    p = data;
    for(i = 0; i < len; i++) {
        printf("%c", isprint(*p) ? *p : '.');
        p++;
    }

    printf("\n");
}

void hexdump(const unsigned char* data, int len) {
    int offset, remaining;

    for (offset = 0, remaining = len; offset < len; offset += 16, remaining -= 16) {
        hexdump_line(data + offset, remaining < 16 ? remaining : 16, offset);
    }
}
