#!/bin/bash

set -euo pipefail

mkdir build
cd build
cmake ..
make