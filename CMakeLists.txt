cmake_minimum_required(VERSION 3.0)
project(usb_capture_dump)

add_executable(
    usb-capture-dump
    hexdump.c
    hexdump.h
    keys.c
    keys.h
    usb-capture-dump.c
    usb-struct.h
)

target_link_libraries(usb-capture-dump pcap)