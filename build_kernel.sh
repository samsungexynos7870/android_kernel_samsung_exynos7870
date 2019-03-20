
#!/bin/bash

export ARCH=arm64
export ANDROID_MAJOR_VERSION=o
export CROSS_COMPILE=~/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-

rm -rf output
mkdir output

#make -C $(pwd) O=output lineage-gtaxllte_defconfig
#make -C $(pwd) O=output lineage-gtaxlwifi_defconfig
#make -C $(pwd) O=output tw-gtaxllte_defconfig
make -C $(pwd) O=output tw-gtaxlwifi_defconfig

make -C $(pwd) O=output -j16
