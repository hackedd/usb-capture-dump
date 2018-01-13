#ifndef HEXDUMP_H
#define HEXDUMP_H

void hexdump_line(const unsigned char* payload, int len, int offset);
void hexdump(const unsigned char* data, int line);

#endif
