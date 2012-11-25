#!/bin/sh
libtoolize &&
aclocal -I build-aux &&
autoconf &&
automake --foreign --add-missing
