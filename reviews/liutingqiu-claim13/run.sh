#!/bin/sh
set -eu

c++ -O3 -std=c++17 -Wall -Wextra -pedantic verify_claim13.cpp -o verify_claim13
./verify_claim13
