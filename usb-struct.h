#ifndef USB_STRUCT_H
#define USB_STRUCT_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t  length;      /* This header length */
    uint64_t  irp_id;      /* I/O Request packet ID */
    uint32_t  status;      /* USB status code (on return from host controller) */
    uint16_t  function;    /* URB Function */
    uint8_t   info;        /* I/O Request info */

    uint16_t  bus;         /* bus (RootHub) number */
    uint16_t  device;      /* device address */
    uint8_t   endpoint;    /* endpoint number and transfer direction */
    uint8_t   transfer;    /* transfer type */

    uint32_t  data_length; /* Data length */
} usbpcap_packet_header;

typedef struct {
    uint8_t modifiers;
    uint8_t unused;
    uint8_t keys[6];
} usb_key_data;

#pragma pack(pop)

#define USBPCAP_TRANSFER_ISOCHRONOUS 0
#define USBPCAP_TRANSFER_INTERRUPT   1
#define USBPCAP_TRANSFER_CONTROL     2
#define USBPCAP_TRANSFER_BULK        3

#define URB_FUNCTION_CONTROL_TRANSFER           0x0008
#define URB_FUNCTION_BULK_OR_INTERRUPT_TRANSFER 0x0009
#define URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE 0x000b

#endif
