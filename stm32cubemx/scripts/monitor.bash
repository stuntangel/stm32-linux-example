#!/bin/bash
set -euox pipefail
cd "$(dirname "$0")/.."

type tio

echo "Quit to ctrl-t + q"

tio -b 115200 /dev/ttyACM0 --map INLCRNL -t -L --log-directory logs
