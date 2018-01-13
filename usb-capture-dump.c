#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>

#include <pcap/pcap.h>
#include <pcap/usb.h>

#include "hexdump.h"
#include "usb-struct.h"
#include "keys.h"

void handle_packet(struct pcap_pkthdr* header, const u_char* packet) {
    usbpcap_packet_header* usb_header;
    usb_key_data* key_data;
    int i;
    char buffer[128];

    assert(header->len == header->caplen);
    assert(header->len >= sizeof(usbpcap_packet_header));

    // hexdump(packet, header->caplen);
    usb_header = (usbpcap_packet_header*)packet;

    // TODO: Print info about device
    // TODO: Add code to handle mice
    // TODO: Separate data from multiple keyboards

    if (usb_header->endpoint & URB_TRANSFER_IN && usb_header->transfer == USBPCAP_TRANSFER_INTERRUPT) {
        assert(header->len >= sizeof(usbpcap_packet_header) + usb_header->data_length);
        assert(usb_header->data_length >= sizeof(usb_key_data));

        // printf("Device: %d.%d.%d\n", usb_header->bus, usb_header->device, usb_header->endpoint & ~URB_TRANSFER_IN);
        // hexdump(packet + sizeof(usbpcap_packet_header), usb_header->data_length);

        key_data = (usb_key_data*)(packet + sizeof(usbpcap_packet_header));
        for (i = 0; i < 6; i += 1) {
            if (key_data->keys[i] == 0) {
                break;
            }

            decode_key(key_data->keys[i], key_data->modifiers, buffer);
            printf("%s", buffer);
        }

        // if (i > 0) {
        //     printf("\n");
        // }
    }
}

int handle_capture(pcap_t* pcap) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int r;

    // TODO: Support other USB captures (http://www.tcpdump.org/linktypes.html)
    int link_type = pcap_datalink(pcap);
    if (link_type != DLT_USBPCAP) {
        fprintf(stderr, "Not a USBPcap device\n");
        pcap_close(pcap);
        return 1;
    }

    while ((r = pcap_next_ex(pcap, &header, &packet)) != -2) {
        if (r == 0) { // read timeout
            continue;
        }
        if (r != 1) {
            fprintf(stderr, "Unable to read packet: %s\n", pcap_geterr(pcap));
            break;
        }

        handle_packet(header, packet);
    }

    printf("\n");

    pcap_close(pcap);
    return 0;
}

int handle_file(char* filename) {
    pcap_t* pcap;
    char errbuf[PCAP_ERRBUF_SIZE];

    if ((pcap = pcap_open_offline(filename, errbuf)) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", filename, errbuf);
        return 1;
    }

    return handle_capture(pcap);
}

void usage(const char* progname) {
    printf("Usage: %s [options] FILE...\n", progname);
    printf("\n");
    printf("Options:\n");
    printf("  -h  print this help\n");
}

int main(int argc, char** argv) {
    int opt;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                usage(argv[0]);
                return 0;

            default:
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "%s: no input files\n", argv[0]);
        return 1;
    }

    for (; optind < argc; optind += 1) {
        if (handle_file(argv[optind]) != 0) {
            return 1;
        }
    }

    return 0;
}
