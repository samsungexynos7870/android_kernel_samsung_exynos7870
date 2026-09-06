cmd_scripts/basic/bin2c := gcc -Wp,-MD,scripts/basic/.bin2c.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -fno-delete-null-pointer-checks     -o scripts/basic/bin2c scripts/basic/bin2c.c  

source_scripts/basic/bin2c := scripts/basic/bin2c.c

deps_scripts/basic/bin2c := \
  /data/data/com.termux/files/usr/bin/../../usr/include/stdio.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/cdefs.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/versioning.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/api-level.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/get_device_api_level_inlines.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/ndk-version.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/types.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/stddef.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_header_macro.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_ptrdiff_t.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_size_t.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_wchar_t.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_null.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stddef_offsetof.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/stdint.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/stdint.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/wchar_limits.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/int-ll64.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/bitsperlong.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/bitsperlong.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/posix_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/stddef.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/compiler_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/compiler.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/posix_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/posix_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/pthread_types.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/stdarg.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_header_macro.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg___gnuc_va_list.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_list.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_arg.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg___va_copy.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_copy.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/string.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/xlocale.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/strcasecmp.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/flock64.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/flock.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/seek_constants.h \

scripts/basic/bin2c: $(deps_scripts/basic/bin2c)

$(deps_scripts/basic/bin2c):
