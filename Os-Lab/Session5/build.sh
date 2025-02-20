#!/bin/bash

compiler=gcc

make || exit 1

gcc test.c -o test ||‌exit 1

insmod ./iutmodule.ko

mknod /dev/saman_headphone c $(cat /proc/devices | grep iut | cut -d' ' -f1) 0 || exit 1

