#!/bin/bash

export ARCH=arm64
export CROSS_COMPILE="ccache /media/astrako/DATOS/toolchain/gcc-linaro-7.5.0/bin/aarch64-linux-gnu-"
export PLATFORM_VERSION=10

make O=./out $1
make O=./out -j$(nproc --all)
