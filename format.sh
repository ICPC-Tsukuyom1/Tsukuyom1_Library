#!/bin/bash

cd `dirname $0`
find . -name "*.cpp" | xargs clang-format -i