#!/bin/bash

./autobuild.sh "cc"

if [ -z $1 ] ; then
    clang-tidy `find . -type d \( -path ./build -o -path ./deps -o -path ./tests \) -prune -o -name '*.cpp' -o -name '*.hpp'`
else
    clang-tidy --fix `find . -type d \( -path ./build -o -path ./deps -o -path ./tests \) -prune -o -name '*.cpp' -o -name '*.hpp'`
fi
