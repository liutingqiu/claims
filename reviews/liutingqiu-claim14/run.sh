#!/bin/sh
set -eu

cc -O3 -std=c11 -Wall -Wextra -pedantic verify_claim14.c -o verify_claim14
./verify_claim14
