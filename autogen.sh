#!/bin/sh
aclocal -I build-aux &&
automake --add-missing --foreign &&
libtoolize &&
aclocal -I build-aux &&
autoconf &&
automake --foreign
