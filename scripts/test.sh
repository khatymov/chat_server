#!/bin/bash

set -euo pipefail

if [ -d build_tests ]; then
  rm -rf ./build_tests
fi

mkdir ./build_tests
cd ./build_tests
cmake ../tests/
make
./run_unit_tests

lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/opt/*' '/usr/*' '*/tests/*' 'build/*' --output-file coverage.info
lcov --list coverage.info

genhtml coverage.info --output-directory out

#google-chrome-stable out/index.html