#!/bin/bash

# Build cscope for dir1
if [ $1 -ge 1 ]; then
    rm -rf cscope.*
    find . -name "*.c" -o -name "*.h" -o -name "*.s" -o -name "*.S" -o -name "*.xml" -o -name "*.cpp" | grep -v -e "/debug/" -e "/unity/" -e "/arch/" > cscope.files
    export TMPDIR=/tmp
    cscope -b
    ctags -R --c-kinds=+p --fields=+S .
fi

# Build cscope for dir2
if [ $1 -ge 2 ]; then
    pushd ../
    rm -rf cscope.*
    find ./builds -name "*.c" -o -name "*.h" -o -name "*.xml" -o -name "*.cpp" | grep -v -e "/debug/" -e "/unity/" -e "/arch/" >> cscope.files
    find ./common -name "*.c" -o -name "*.h" -o -name "*.s" -o -name "*.S" -o -name "*.xml" -o -name "*.cpp" | grep -v -e "/debug/" -e "/unity/" -e "/arch/" >> cscope.files
    export TMPDIR=/tmp
    cscope -b
    popd
fi

# Build cscope for dir3
if [ $1 -ge 3 ]; then
    pushd ../../../dir3
    rm -rf cscope.*
    find . -name "*.c" -o -name "*.h" -o -name "*.s" -o -name "*.S" -o -name "*.xml" -o -name "*.cpp" > cscope.files
    export TMPDIR=/tmp
    cscope -b
    popd
fi
