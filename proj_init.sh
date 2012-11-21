#!/bin/sh
./autogen.sh &&
mkdir -p bin/Debug &&
mkdir -p bin/Release &&
cd bin/Debug &&
../../configure CFLAGS="-O0 -ggdb" CXXFLAGS="-O0 -ggdb" &&
cd ../../bin/Release &&
../../configure
exit $?

