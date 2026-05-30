#!/bin/bash

rm -v ./pizzad
gcc ./*.c -lsystemd -o ./pizzad
printf "rebuilt pizzad...\n"
