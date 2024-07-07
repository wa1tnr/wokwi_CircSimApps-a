#!/bin/sh

# point to mose recent (re)location of actively developed code:
export CURRENT=sbx-cc
export PICO_SDK_PATH=../../pico-sdk

# change this line to point to the dev toolchain:
# export SOME_BIN_DIR=$HOME/this/dir/bin

# EXAMPLE for LINE 6 changes (your local compiler)
#
#     points to your preferred version of arm-none-eabi-gcc:
#     export SOME_BIN_DIR=$HOME/tools/compilers/this_compiler/bin


# optional pre-cleaning of unwanted files:
./cleaner.sh
cmake .. -D"PICO_BOARD=pico" -D"PICO_TOOLCHAIN_PATH=$SOME_BIN_DIR"

cd ${CURRENT}
make

exit 0

#END.
