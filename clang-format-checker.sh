#!/bin/bash

if [ -z $1 ] ; then
    clang-format `find . -name "*.cpp" -o -name "*.hpp" -not -path "./build/*" -not -path "./deps/*"`
else
    clang-format -i `find . -name "*.cpp" -o -name "*.hpp" -not -path "./build/*" -not -path "./deps/*"`
fi
