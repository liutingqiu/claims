#!/bin/sh
set -eu

c++ -O3 -std=c++17 -Wall -Wextra -pedantic verify_claim10.cpp -o verify_claim10
./verify_claim10
