#!/usr/bin/env bash
set -eu; cd "$(dirname "$0")"
curl -sL -o phoible.csv https://raw.githubusercontent.com/phoible/dev/adc867f4dd2be1bf4262395c69c33fe8c4a7e75e/data/phoible.csv
curl -sL -o grambank-values.csv https://raw.githubusercontent.com/grambank/grambank/37f73da55cf8b426c82383f46a972bc59ce6cf76/cldf/values.csv
echo "866d36bc83ab21bdb5837ffa63dc5993  phoible.csv
60f1ae344334037c5064ce532300fae5  grambank-values.csv" | md5sum -c -
