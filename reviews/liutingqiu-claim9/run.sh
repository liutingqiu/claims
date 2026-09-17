#!/usr/bin/env bash
set -euo pipefail

g++ -std=c++17 -O3 -DNDEBUG -Wall -Wextra -pedantic main.cpp -o claim9
./claim9
