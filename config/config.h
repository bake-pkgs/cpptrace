/* Hand-maintained libdwarf config.h (upstream generates it per-build from
 * cmake/config.h.in). Unix-only: windows builds don't compile libdwarf.
 * Decompression on (zlib + zstd via bake-pkgs), mmap on. */
#define PACKAGE_NAME "libdwarf"
#define PACKAGE_VERSION "2.1.0"
#define STDC_HEADERS 1
#define HAVE_DLFCN_H 1
#define HAVE_FCNTL_H 1
#define HAVE_MALLOC_H 1
#define HAVE_STDINT_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
#define HAVE_FULL_MMAP 1
#define HAVE_ZLIB 1
#define HAVE_ZLIB_H 1
#define HAVE_ZSTD 1
#define HAVE_ZSTD_H 1
