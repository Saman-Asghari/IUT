#!/bin/bash

rm -f test || exit 1

rm -f /dev/saman_headphone || exit 1

rmmod iutmodule

make clean || exit 1