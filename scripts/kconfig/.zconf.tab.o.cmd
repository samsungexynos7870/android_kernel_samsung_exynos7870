cmd_scripts/kconfig/zconf.tab.o := gcc -Wp,-MD,scripts/kconfig/.zconf.tab.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -fno-delete-null-pointer-checks   -DNCURSES_WIDECHAR -I/data/data/com.termux/files/usr/include -DCURSES_LOC="<ncurses.h>" -DNCURSES_WIDECHAR=1 -DLOCALE  -Iscripts/kconfig -c -o scripts/kconfig/zconf.tab.o scripts/kconfig/zconf.tab.c

source_scripts/kconfig/zconf.tab.o := scripts/kconfig/zconf.tab.c

deps_scripts/kconfig/zconf.tab.o := \
  /data/data/com.termux/files/usr/bin/../../usr/include/ctype.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/cdefs.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/versioning.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/api-level.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/get_device_api_level_inlines.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/ndk-version.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/xlocale.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/stdarg.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_header_macro.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg___gnuc_va_list.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_list.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_arg.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg___va_copy.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/__stdarg_va_copy.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/stdio.h \
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
  /data/data/com.termux/files/usr/bin/../../usr/include/string.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/strcasecmp.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/flock64.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/flock.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/seek_constants.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/stdlib.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/alloca.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/wait.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/wait.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/malloc.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/legacy_stdlib_inlines.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/stdlib_inlines.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/stdbool.h \
  scripts/kconfig/lkc.h \
    $(wildcard include/config/.h) \
    $(wildcard include/config/prefix.h) \
    $(wildcard include/config/list.h) \
    $(wildcard include/config/y.h) \
  scripts/kconfig/expr.h \
    $(wildcard include/config/config.h) \
  /data/data/com.termux/files/usr/bin/../../usr/include/assert.h \
  scripts/kconfig/list.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/libintl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/errno.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/errno.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/errno.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/errno.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/errno-base.h \
  scripts/kconfig/lkc_proto.h \
  scripts/kconfig/zconf.hash.c \
  scripts/kconfig/zconf.lex.c \
  /data/data/com.termux/files/usr/lib/clang/21/include/limits.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/limits.h \
  /data/data/com.termux/files/usr/lib/clang/21/include/float.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/limits.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/posix_limits.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/unistd.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/select.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/time.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/timespec.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/time_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/signal.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/sigcontext.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/sve_context.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/signal_types.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/signal.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/signal.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/signal.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/signal-defs.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/aarch64-linux-android/asm/siginfo.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/asm-generic/siginfo.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/ucontext.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/user.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/page_size.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/getentropy.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/getopt.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/ioctl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/lockf.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/sysconf.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/android/legacy_unistd_inlines.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/bits/swab.h \
  scripts/kconfig/util.c \
  scripts/kconfig/confdata.c \
    $(wildcard include/config/autoconfig.h) \
    $(wildcard include/config/overwriteconfig.h) \
    $(wildcard include/config/autoheader.h) \
    $(wildcard include/config/tristate.h) \
    $(wildcard include/config/probability.h) \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/stat.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/stat.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/fadvise.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/falloc.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/fcntl.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/openat2.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/linux/uio.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/time.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/time.h \
  scripts/kconfig/expr.c \
  scripts/kconfig/symbol.c \
  /data/data/com.termux/files/usr/bin/../../usr/include/regex.h \
  /data/data/com.termux/files/usr/bin/../../usr/include/sys/utsname.h \
  scripts/kconfig/menu.c \

scripts/kconfig/zconf.tab.o: $(deps_scripts/kconfig/zconf.tab.o)

$(deps_scripts/kconfig/zconf.tab.o):
