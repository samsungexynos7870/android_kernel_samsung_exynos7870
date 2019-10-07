#!/bin/bash

export ARCH=arm64
export CROSS_COMPILE=~/android/kernel/toolchain/gcc-linaro-7.4.1/bin/aarch64-linux-gnu-
export ANDROID_MAJOR_VERSION=p

make O=./out exynos7870-a3y17lte_defconfig
make O=./out -j16
