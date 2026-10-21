typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef int __sig_atomic_t;

enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
extern const unsigned short int **__ctype_b_loc (void)
     ;
extern const __int32_t **__ctype_tolower_loc (void)
     ;
extern const __int32_t **__ctype_toupper_loc (void)
     ;
extern int isalnum (int) ;
extern int isalpha (int) ;
extern int iscntrl (int) ;
extern int isdigit (int) ;
extern int islower (int) ;
extern int isgraph (int) ;
extern int isprint (int) ;
extern int ispunct (int) ;
extern int isspace (int) ;
extern int isupper (int) ;
extern int isxdigit (int) ;
extern int tolower (int __c) ;
extern int toupper (int __c) ;
extern int isblank (int) ;
extern int isascii (int __c) ;
extern int toascii (int __c) ;
extern int _toupper (int) ;
extern int _tolower (int) ;
struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
};
typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
extern int isalnum_l (int, locale_t) ;
extern int isalpha_l (int, locale_t) ;
extern int iscntrl_l (int, locale_t) ;
extern int isdigit_l (int, locale_t) ;
extern int islower_l (int, locale_t) ;
extern int isgraph_l (int, locale_t) ;
extern int isprint_l (int, locale_t) ;
extern int ispunct_l (int, locale_t) ;
extern int isspace_l (int, locale_t) ;
extern int isupper_l (int, locale_t) ;
extern int isxdigit_l (int, locale_t) ;
extern int isblank_l (int, locale_t) ;
extern int __tolower_l (int __c, locale_t __l) ;
extern int tolower_l (int __c, locale_t __l) ;
extern int __toupper_l (int __c, locale_t __l) ;
extern int toupper_l (int __c, locale_t __l) ;

typedef int BOOLEAN;
typedef char *string;

typedef long unsigned int size_t;
typedef __gnuc_va_list;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
struct _IO_FILE;
typedef struct _IO_FILE __FILE;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;
typedef void _IO_lock_t;
struct _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);
typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);
typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);
typedef int cookie_close_function_t (void *__cookie);
typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
typedef __gnuc_va_list va_list;
typedef __off_t off_t;
typedef __ssize_t ssize_t;
typedef __fpos_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename) ;
extern int rename (const char *__old, const char *__new) ;
extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) ;
extern int fclose (FILE *__stream) ;
extern FILE *tmpfile (void)
  ;
extern char *tmpnam (char[20]) ;
extern char *tmpnam_r (char __s[20]) ;
extern char *tempnam (const char *__dir, const char *__pfx)
   ;
extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char * __filename,
      const char * __modes)
  ;
extern FILE *freopen (const char * __filename,
        const char * __modes,
        FILE * __stream) ;
extern FILE *fdopen (int __fd, const char *__modes)
  ;
extern FILE *fopencookie (void * __magic_cookie,
     const char * __modes,
     cookie_io_functions_t __io_funcs)
  ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc)
  ;
extern void setbuf (FILE * __stream, char * __buf)
  ;
extern int setvbuf (FILE * __stream, char * __buf,
      int __modes, size_t __n) ;
extern void setbuffer (FILE * __stream, char * __buf,
         size_t __size) ;
extern void setlinebuf (FILE *__stream) ;
extern int fprintf (FILE * __stream,
      const char * __format, ...) ;
extern int printf (const char * __format, ...);
extern int sprintf (char * __s,
      const char * __format, ...) ;
extern int vfprintf (FILE * __s, const char * __format,
       __gnuc_va_list __arg) ;
extern int vprintf (const char * __format, __gnuc_va_list __arg);
extern int vsprintf (char * __s, const char * __format,
       __gnuc_va_list __arg) ;
extern int snprintf (char * __s, size_t __maxlen,
       const char * __format, ...)
     ;
extern int vsnprintf (char * __s, size_t __maxlen,
        const char * __format, __gnuc_va_list __arg)
     ;
extern int vasprintf (char ** __ptr, const char * __f,
        __gnuc_va_list __arg)
     ;
extern int __asprintf (char ** __ptr,
         const char * __fmt, ...)
     ;
extern int asprintf (char ** __ptr,
       const char * __fmt, ...)
     ;
extern int vdprintf (int __fd, const char * __fmt,
       __gnuc_va_list __arg)
     ;
extern int dprintf (int __fd, const char * __fmt, ...)
     ;
extern int fscanf (FILE * __stream,
     const char * __format, ...) ;
extern int scanf (const char * __format, ...) ;
extern int sscanf (const char * __s,
     const char * __format, ...) ;
extern int fscanf (FILE * __stream, const char * __format, ...) ;
extern int scanf (const char * __format, ...) ;
extern int sscanf (const char * __s, const char * __format, ...) ;
extern int vfscanf (FILE * __s, const char * __format,
      __gnuc_va_list __arg)
     ;
extern int vscanf (const char * __format, __gnuc_va_list __arg)
     ;
extern int vsscanf (const char * __s,
      const char * __format, __gnuc_va_list __arg)
     ;
extern int vfscanf (FILE * __s, const char * __format, __gnuc_va_list __arg)
     ;
extern int vscanf (const char * __format, __gnuc_va_list __arg)
     ;
extern int vsscanf (const char * __s, const char * __format, __gnuc_va_list __arg)
     ;
extern int fgetc (FILE *__stream) ;
extern int getc (FILE *__stream) ;
extern int getchar (void);
extern int getc_unlocked (FILE *__stream) ;
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream) ;
extern int fputc (int __c, FILE *__stream) ;
extern int putc (int __c, FILE *__stream) ;
extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream) ;
extern int putc_unlocked (int __c, FILE *__stream) ;
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream) ;
extern int putw (int __w, FILE *__stream) ;
extern char *fgets (char * __s, int __n, FILE * __stream)
     ;
extern __ssize_t __getdelim (char ** __lineptr,
                             size_t * __n, int __delimiter,
                             FILE * __stream) ;
extern __ssize_t getdelim (char ** __lineptr,
                           size_t * __n, int __delimiter,
                           FILE * __stream) ;
extern __ssize_t getline (char ** __lineptr,
                          size_t * __n,
                          FILE * __stream) ;
extern int fputs (const char * __s, FILE * __stream)
  ;
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream) ;
extern size_t fread (void * __ptr, size_t __size,
       size_t __n, FILE * __stream)
  ;
extern size_t fwrite (const void * __ptr, size_t __size,
        size_t __n, FILE * __s) ;
extern size_t fread_unlocked (void * __ptr, size_t __size,
         size_t __n, FILE * __stream)
  ;
extern size_t fwrite_unlocked (const void * __ptr, size_t __size,
          size_t __n, FILE * __stream)
  ;
extern int fseek (FILE *__stream, long int __off, int __whence)
  ;
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream) ;
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  ;
extern __off_t ftello (FILE *__stream) ;
extern int fgetpos (FILE * __stream, fpos_t * __pos)
  ;
extern int fsetpos (FILE *__stream, const fpos_t *__pos) ;
extern void clearerr (FILE *__stream) ;
extern int feof (FILE *__stream) ;
extern int ferror (FILE *__stream) ;
extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;
extern void perror (const char *__s) ;
extern int fileno (FILE *__stream) ;
extern int fileno_unlocked (FILE *__stream) ;
extern int pclose (FILE *__stream) ;
extern FILE *popen (const char *__command, const char *__modes)
  ;
extern char *ctermid (char *__s)
  ;
extern void flockfile (FILE *__stream) ;
extern int ftrylockfile (FILE *__stream) ;
extern void funlockfile (FILE *__stream) ;
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);

typedef int wchar_t;

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;
 typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
extern size_t __ctype_get_mb_cur_max (void) ;
extern double atof (const char *__nptr)
     ;
extern int atoi (const char *__nptr)
     ;
extern long int atol (const char *__nptr)
     ;
 extern long long int atoll (const char *__nptr)
     ;
extern double strtod (const char * __nptr,
        char ** __endptr)
     ;
extern float strtof (const char * __nptr,
       char ** __endptr) ;
extern long double strtold (const char * __nptr,
       char ** __endptr)
     ;
extern long int strtol (const char * __nptr,
   char ** __endptr, int __base)
     ;
extern unsigned long int strtoul (const char * __nptr,
      char ** __endptr, int __base)
     ;

extern long long int strtoq (const char * __nptr,
        char ** __endptr, int __base)
     ;

extern unsigned long long int strtouq (const char * __nptr,
           char ** __endptr, int __base)
     ;

extern long long int strtoll (const char * __nptr,
         char ** __endptr, int __base)
     ;

extern unsigned long long int strtoull (const char * __nptr,
     char ** __endptr, int __base)
     ;
extern char *l64a (long int __n) ;
extern long int a64l (const char *__s)
     ;

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef __clock_t clock_t;
typedef __clockid_t clockid_t;
typedef __time_t time_t;
typedef __timer_t timer_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
typedef int register_t ;
static __uint16_t
__bswap_16 (__uint16_t __bsx)
{
  return __builtin_bswap16 (__bsx);
}
static __uint32_t
__bswap_32 (__uint32_t __bsx)
{
  return __builtin_bswap32 (__bsx);
}
 static __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
static __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}
static __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}
static __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
typedef __sigset_t sigset_t;
struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
typedef __suseconds_t suseconds_t;
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set * __readfds,
     fd_set * __writefds,
     fd_set * __exceptfds,
     struct timeval * __timeout);
extern int pselect (int __nfds, fd_set * __readfds,
      fd_set * __writefds,
      fd_set * __exceptfds,
      const struct timespec * __timeout,
      const __sigset_t * __sigmask);

typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef union
{
  unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;
  unsigned int __nusers;
  int __kind;
  short __spins;
  short __elision;
  __pthread_list_t __list;
};
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;
  int __cur_writer;
  int __shared;
  signed char __rwelision;
  unsigned char __pad1[7];
  unsigned long int __pad2;
  unsigned int __flags;
};
struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;
typedef struct
{
  int __data ;
} __once_flag;
typedef unsigned long int pthread_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
union pthread_attr_t
{
  char __size[56];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;
typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  long long int __align;
} pthread_cond_t;
typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;

extern long int random (void) ;
extern void srandom (unsigned int __seed) ;
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) ;
extern char *setstate (char *__statebuf) ;
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data * __buf,
       int32_t * __result) ;
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     ;
extern int initstate_r (unsigned int __seed, char * __statebuf,
   size_t __statelen,
   struct random_data * __buf)
     ;
extern int setstate_r (char * __statebuf,
         struct random_data * __buf)
     ;
extern int rand (void) ;
extern void srand (unsigned int __seed) ;
extern int rand_r (unsigned int *__seed) ;
extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;
extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3])
     ;
extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3])
     ;
extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     ;
extern void lcong48 (unsigned short int __param[7]) ;
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data * __buffer,
        double * __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        double * __result) ;
extern int lrand48_r (struct drand48_data * __buffer,
        long int * __result)
     ;
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        long int * __result)
     ;
extern int mrand48_r (struct drand48_data * __buffer,
        long int * __result)
     ;
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        long int * __result)
     ;
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     ;
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) ;
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     ;
extern __uint32_t arc4random (void)
     ;
extern void arc4random_buf (void *__buf, size_t __size)
     ;
extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     ;
extern void *malloc (size_t __size)
     ;
extern void *calloc (size_t __nmemb, size_t __size)
     ;
extern void *realloc (void *__ptr, size_t __size)
     ;
extern void free (void *__ptr) ;
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
    
    
    ;
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     ;

extern void *alloca (size_t __size) ;

extern void *valloc (size_t __size)
     ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
    
     ;
extern void abort (void) ;
extern int atexit (void (*__func) (void)) ;
extern int at_quick_exit (void (*__func) (void)) ;
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     ;
extern void exit (int __status) ;
extern void quick_exit (int __status) ;
extern void _Exit (int __status) ;
extern char *getenv (const char *__name) ;
extern int putenv (char *__string) ;
extern int setenv (const char *__name, const char *__value, int __replace)
     ;
extern int unsetenv (const char *__name) ;
extern int clearenv (void) ;
extern char *mktemp (char *__template) ;
extern int mkstemp (char *__template) ;
extern int mkstemps (char *__template, int __suffixlen) ;
extern char *mkdtemp (char *__template) ;
extern int system (const char *__command) ;
extern char *realpath (const char * __name,
         char * __resolved) ;
typedef int (*__compar_fn_t) (const void *, const void *);
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) ;
extern int abs (int __x) ;
extern long int labs (long int __x) ;
 extern long long int llabs (long long int __x)
     ;
extern div_t div (int __numer, int __denom)
     ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     ;
 extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     ;
extern char *ecvt (double __value, int __ndigit, int * __decpt,
     int * __sign) ;
extern char *fcvt (double __value, int __ndigit, int * __decpt,
     int * __sign) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     ;
extern char *qecvt (long double __value, int __ndigit,
      int * __decpt, int * __sign)
     ;
extern char *qfcvt (long double __value, int __ndigit,
      int * __decpt, int * __sign)
     ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     ;
extern int ecvt_r (double __value, int __ndigit, int * __decpt,
     int * __sign, char * __buf,
     size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int * __decpt,
     int * __sign, char * __buf,
     size_t __len) ;
extern int qecvt_r (long double __value, int __ndigit,
      int * __decpt, int * __sign,
      char * __buf, size_t __len)
     ;
extern int qfcvt_r (long double __value, int __ndigit,
      int * __decpt, int * __sign,
      char * __buf, size_t __len)
     ;
extern int mblen (const char *__s, size_t __n) ;
extern int mbtowc (wchar_t * __pwc,
     const char * __s, size_t __n) ;
extern int wctomb (char *__s, wchar_t __wchar) ;
extern size_t mbstowcs (wchar_t * __pwcs,
   const char * __s, size_t __n)
    ;
extern size_t wcstombs (char * __s,
   const wchar_t * __pwcs, size_t __n)
    
 
  ;
extern int rpmatch (const char *__response) ;
extern int getsubopt (char ** __optionp,
        char *const * __tokens,
        char ** __valuep)
     ;
extern int getloadavg (double __loadavg[], int __nelem)
     ;


extern void *memcpy (void * __dest, const void * __src,
       size_t __n) ;
extern void *memmove (void *__dest, const void *__src, size_t __n)
     ;
extern void *memccpy (void * __dest, const void * __src,
        int __c, size_t __n)
    ;
extern void *memset (void *__s, int __c, size_t __n) ;
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     ;
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     ;
extern void *memchr (const void *__s, int __c, size_t __n)
      ;
extern char *strcpy (char * __dest, const char * __src)
     ;
extern char *strncpy (char * __dest,
        const char * __src, size_t __n)
     ;
extern char *strcat (char * __dest, const char * __src)
     ;
extern char *strncat (char * __dest, const char * __src,
        size_t __n) ;
extern int strcmp (const char *__s1, const char *__s2)
     ;
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     ;
extern int strcoll (const char *__s1, const char *__s2)
     ;
extern size_t strxfrm (char * __dest,
         const char * __src, size_t __n)
    ;
extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     ;
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l)
     ;
extern char *strdup (const char *__s)
     ;
extern char *strndup (const char *__string, size_t __n)
     ;
extern char *strchr (const char *__s, int __c)
     ;
extern char *strrchr (const char *__s, int __c)
     ;
extern char *strchrnul (const char *__s, int __c)
     ;
extern size_t strcspn (const char *__s, const char *__reject)
     ;
extern size_t strspn (const char *__s, const char *__accept)
     ;
extern char *strpbrk (const char *__s, const char *__accept)
     ;
extern char *strstr (const char *__haystack, const char *__needle)
     ;
extern char *strtok (char * __s, const char * __delim)
     ;
extern char *__strtok_r (char * __s,
    const char * __delim,
    char ** __save_ptr)
     ;
extern char *strtok_r (char * __s, const char * __delim,
         char ** __save_ptr)
     ;
extern char *strcasestr (const char *__haystack, const char *__needle)
     ;
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
    
   
    ;
extern void *__mempcpy (void * __dest,
   const void * __src, size_t __n)
     ;
extern void *mempcpy (void * __dest,
        const void * __src, size_t __n)
     ;
extern size_t strlen (const char *__s)
     ;
extern size_t strnlen (const char *__string, size_t __maxlen)
     ;
extern char *strerror (int __errnum) ;
extern int strerror_r (int __errnum, char *__buf, size_t __buflen)
    ;
extern char *strerror_l (int __errnum, locale_t __l) ;

extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     ;
extern void bcopy (const void *__src, void *__dest, size_t __n)
  ;
extern void bzero (void *__s, size_t __n) ;
extern char *index (const char *__s, int __c)
     ;
extern char *rindex (const char *__s, int __c)
     ;
extern int ffs (int __i) ;
extern int ffsl (long int __l) ;
 extern int ffsll (long long int __ll)
     ;
extern int strcasecmp (const char *__s1, const char *__s2)
     ;
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     ;
extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     ;
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     ;

extern void explicit_bzero (void *__s, size_t __n)
    ;
extern char *strsep (char ** __stringp,
       const char * __delim)
     ;
extern char *strsignal (int __sig) ;
extern char *__stpcpy (char * __dest, const char * __src)
     ;
extern char *stpcpy (char * __dest, const char * __src)
     ;
extern char *__stpncpy (char * __dest,
   const char * __src, size_t __n)
     ;
extern char *stpncpy (char * __dest,
        const char * __src, size_t __n)
     ;
extern size_t strlcpy (char * __dest,
         const char * __src, size_t __n)
  ;
extern size_t strlcat (char * __dest,
         const char * __src, size_t __n)
  ;

typedef struct stream_type {
                               FILE *fp;
                               int stream_ind;
                               char stream[80];
                            } *character_stream;
typedef char CHARACTER;
character_stream open_character_stream(string FILENAME);
CHARACTER get_char(character_stream stream_ptr);
BOOLEAN is_end_of_character_stream(character_stream stream_ptr);
typedef struct token_stream_type {
                             character_stream ch_stream;
                          } *token_stream;
typedef struct token_type {
                                int token_id;
                                char token_string[80];
                          } *token;
token_stream open_token_stream(string FILENAME);
token get_token(token_stream tstream_ptr);
BOOLEAN is_eof_token(token t);
static int default1[]={
                 54, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 51, -2, -1,
                 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                 -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1,
                 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                 -1, 52, -3, -1 ,-1, -1, -1, -1, -1, -1
               };
static int base[] ={
                  -32, -96,-105, -93, -94, -87, -1, -97, -86, -1,
                  -99, -1, -72, -1, -80, -82, -1, 53, 43, -1,
                  -1, -1, -1, -1, -1, -1, 133, -1, 233, -1,
                  -1, 0, -1, -1, -1, -1, -1, -1, -1, -1,
                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                  -1, 46, 40, -1, 251, -1, -1, -1, -1, -1
              };
static int next[] = {
                  0, 2, 26, 28, 3, 4, 5, 23, 19, 20,
                  6, -1, 25, 8, 9, 11, 18, 18, 18, 18,
                 18, 18, 18, 18, 18, 18, -1, 30, -1, 31,
                 13, 15, 16, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 21,
                 -1, 22, 32, -1, 24, 7, 17, 17, 17, 17,
                 17, 17, 17, 12, 17, 17, 1, 17, 17, 10,
                 17, 17, 17, 17, 17, 17, 17, 17, 14, 17,
                 17, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 17, 17, -1, -1, 26, 26, 27, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                  0, 0, -1, -1, -1, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
            };
static int check[] = { 0, 1, 0, 0, 2, 3, 4, 0, 0, 0,
                  5, -1, 0, 7, 8, 10, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, -1, 0, -1, 0,
                 12, 14, 15, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 -1, 0, 31, -1, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18, 17, 17, 17, 17, 17, 17, 17, 17, 17,
                 17, 51, 51, 51, 51, 51, 51, 51, 51, 51,
                 51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
                 51, 51, 51, 51, 51, 51, 51, 52, 52, 52,
                 52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
                 52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
                 52, 52, 52, -1, -1, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
                 54, 54, -1, -1, -1, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
                 28, 28, 28, 28, 28, 28, 28, 28, 28, 28
              };
token numeric_case(token_stream tstream_ptr, token token_ptr, char ch, char token_str[], int token_ind);
token error_or_eof_case(token_stream tstream_ptr, token token_ptr, int cu_state, char token_str[], int token_ind, char ch);
int check_delimiter(char ch);
int keyword(int state);
int special(int state);
int skip(character_stream stream_ptr);
int constant(int state, char token_str[], int token_ind);
int next_state(int state, char ch);
int get_actual_token(char token_str[], int token_ind);
character_stream open_character_stream(string FILENAME)
{
      character_stream stream_ptr;
      stream_ptr=(character_stream)malloc(sizeof(struct stream_type));
      stream_ptr->stream_ind=5;
      stream_ptr->stream[5]='\0';
      if(FILENAME == ((void *)0))
          stream_ptr->fp=stdin;
      else if((stream_ptr->fp=fopen(FILENAME,"r"))==((void *)0))
           {
               fprintf(stdout, "The file %s doesn't exists\n",FILENAME);
               exit(0);
           }
      return(stream_ptr);
}
CHARACTER get_char(character_stream stream_ptr)
{
      if(stream_ptr->stream[stream_ptr->stream_ind] == '\0')
      {
              if(fgets(stream_ptr->stream+5,80-5,stream_ptr->fp) == ((void *)0))
                    stream_ptr->stream[5]=(-1);
              stream_ptr->stream_ind=5;
      }
      return(stream_ptr->stream[(stream_ptr->stream_ind)++]);
}
BOOLEAN is_end_of_character_stream(character_stream stream_ptr)
{
      if(stream_ptr->stream[stream_ptr->stream_ind-1] == (-1))
            return(1);
      else
            return(0);
}
int unget_char(CHARACTER ch, character_stream stream_ptr)
{
      if(stream_ptr->stream_ind == 0)
          return 0;
      else
          stream_ptr->stream[--(stream_ptr->stream_ind)]=ch;
      return 0;
}
token_stream open_token_stream(string FILENAME)
{
    token_stream token_ptr;
    token_ptr=(token_stream)malloc(sizeof(struct token_stream_type));
    token_ptr->ch_stream=open_character_stream(FILENAME);
    return(token_ptr);
}
token get_token(token_stream tstream_ptr)
{
      char token_str[80];
      int token_ind;
      token token_ptr;
      CHARACTER ch;
      int cu_state,next_st,token_found;
      token_ptr=(token)(malloc(sizeof(struct token_type)));
      ch=get_char(tstream_ptr->ch_stream);
      cu_state=token_ind=token_found=0;
      while(!token_found)
      {
   if(token_ind < 80)
   {
       token_str[token_ind++]=ch;
       next_st=next_state(cu_state,ch);
   }
   else
   {
       next_st = -1;
   }
   if (next_st == -1) {
       return(error_or_eof_case(tstream_ptr,
           token_ptr,cu_state,token_str,token_ind,ch));
   } else if (next_st == -2) {
       return(numeric_case(tstream_ptr,token_ptr,ch,
      token_str,token_ind));
   } else if (next_st == -3) {
       token_ptr->token_id=17;
       unget_char(ch,tstream_ptr->ch_stream);
       token_ind--;
       get_actual_token(token_str,token_ind);
       strcpy(token_ptr->token_string,token_str);
       return(token_ptr);
   }
   switch(next_st)
            {
                 default : break;
                 case 6 :
                 case 9 :
                 case 11 :
                 case 13 :
                 case 16 : ch=get_char(tstream_ptr->ch_stream);
                           if(check_delimiter(ch)==1)
                           {
                                 token_ptr->token_id=keyword(next_st);
                                 unget_char(ch,tstream_ptr->ch_stream);
                                 token_ptr->token_string[0]='\0';
                                 return(token_ptr);
                           }
                           unget_char(ch,tstream_ptr->ch_stream);
                           break;
                 case 19 :
                 case 20 :
                 case 21 :
                 case 22 :
                 case 23 :
                 case 24 :
                 case 25 :
                 case 32 : token_ptr->token_id=special(next_st);
                           token_ptr->token_string[0]='\0';
                           return(token_ptr);
                 case 27 :
                 case 29 : token_ptr->token_id=constant(next_st,token_str,token_ind);
                           get_actual_token(token_str,token_ind);
                           strcpy(token_ptr->token_string,token_str);
                           return(token_ptr);
                 case 30 :
                           skip(tstream_ptr->ch_stream);
                           token_ind=next_st=0;
                           break;
            }
            cu_state=next_st;
            ch=get_char(tstream_ptr->ch_stream);
      }
      return(((void *)0));
}
token numeric_case(token_stream tstream_ptr, token token_ptr, char ch, char token_str[], int token_ind)
{
        if(check_delimiter(ch)!=1)
        {
            token_ptr->token_id=-1;
            while(check_delimiter(ch)==0)
     {
  if(token_ind >= 80) break;
  token_str[token_ind++]=ch=get_char(tstream_ptr->ch_stream);
     }
            unget_char(ch,tstream_ptr->ch_stream);
            token_ind--;
            get_actual_token(token_str,token_ind);
            strcpy(token_ptr->token_string,token_str);
            return(token_ptr);
        }
        token_ptr->token_id=18;
        unget_char(ch,tstream_ptr->ch_stream);
        token_ind--;
        get_actual_token(token_str,token_ind);
        strcpy(token_ptr->token_string,token_str);
        return(token_ptr);
}
token error_or_eof_case(token_stream tstream_ptr, token token_ptr, int cu_state, char token_str[], int token_ind, char ch)
{
      if(is_end_of_character_stream(tstream_ptr->ch_stream))
      {
            token_ptr->token_id = 0;
            token_ptr->token_string[0]='\0';
            return(token_ptr);
      }
      if(cu_state !=0)
      {
            unget_char(ch,tstream_ptr->ch_stream);
            token_ind--;
      }
      token_ptr->token_id=-1;
      get_actual_token(token_str,token_ind);
      strcpy(token_ptr->token_string,token_str);
      return(token_ptr);
}
int check_delimiter(char ch)
{
      if(!((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISalpha) && !((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISdigit))
          return(1);
      return(0);
}
int keyword(int state)
{
      switch(state)
      {
          case 6 : return(6);
          case 9 : return(9);
          case 11: return(11);
          case 13: return(13);
          case 16: return(16);
          default: fprintf(stdout, "error\n");break;
      }
      exit(0);
}
int special(int state)
{
     switch(state)
     {
         case 19: return(19);
         case 20: return(20);
         case 21: return(21);
         case 22: return(22);
         case 23: return(23);
         case 24: return(24);
         case 25: return(25);
         case 32: return(32);
         default: fprintf(stdout, "error\n");break;
     }
     exit(0);
}
int skip(character_stream stream_ptr)
{
        char c;
        while((c=get_char(stream_ptr))!='\n' &&
               !is_end_of_character_stream(stream_ptr))
             ;
 if(c==(-1)) unget_char(c, stream_ptr);
        return 0;
}
int constant(int state, char token_str[], int token_ind)
{
     switch(state)
     {
         case 27 : return(27);
         case 29 : token_str[token_ind-2]=' '; return(29);
         default : return(-1);
     }
}
int next_state(int state, char ch)
{
    if(state < 0)
      return(state);
    if(base[state]+ch >= 0)
    {
        if(check[base[state]+ch] == state)
             return(next[base[state]+ch]);
        else
              return(next_state(default1[state],ch));
    }
    else
        return(next_state(default1[state],ch));
}
BOOLEAN is_eof_token(token t)
{
    if(t->token_id==0)
        return(1);
    return(0);
}
BOOLEAN print_token(token token_ptr)
{
     switch(token_ptr->token_id)
     {
          case -1 : fprintf(stdout, "error,\t\"");fprintf(stdout, "%s",token_ptr->token_string);
                       fprintf(stdout, "\".\n");return(1);
          case 0 : fprintf(stdout, "eof.\n");return(1);
          case 6 : fprintf(stdout, "keyword,\t\"lambda\".\n");return(1);
          case 9 : fprintf(stdout, "keyword,\t\"and\".\n");return(1);
          case 11: fprintf(stdout, "keyword,\t\"or\".\n");return(1);
          case 13: fprintf(stdout, "keyword,\t\"if\".\n");return(1);
          case 16: fprintf(stdout, "keyword,\t\"xor\".\n");return(1);
          case 17: fprintf(stdout, "identifier,\t\"");fprintf(stdout, "%s",token_ptr->token_string);
                   fprintf(stdout, "\".\n");return(1);
          case 18: fprintf(stdout, "numeric,\t");fprintf(stdout, "%s",token_ptr->token_string);
                   fprintf(stdout, ".\n");return(1);
          case 19: fprintf(stdout, "lparen.\n");return(1);
          case 20: fprintf(stdout, "rparen.\n");return(1);
          case 21: fprintf(stdout, "lsquare.\n");return(1);
          case 22: fprintf(stdout, "rsquare.\n");return(1);
          case 23: fprintf(stdout, "quote.\n");return(1);
          case 24: fprintf(stdout, "bquote.\n");return(1);
          case 25: fprintf(stdout, "comma.\n");return(1);
          case 27: fprintf(stdout, "string,\t");fprintf(stdout, "%s",token_ptr->token_string);
                   fprintf(stdout, ".\n");return(1);
          case 29: fprintf(stdout, "character,\t\"");fprintf(stdout, "%s",token_ptr->token_string);
                   fprintf(stdout, "\".\n");return(1);
          case 32: fprintf(stdout, "keyword,\t\"=>\".\n");return(1);
          default: break;
      }
      return(0);
}
int get_actual_token(char token_str[], int token_ind)
{
          int ind,start;
          for(ind=token_ind;ind>0 && ((*__ctype_b_loc ())[(int) ((token_str[ind-1]))] & (unsigned short int) _ISspace);--ind);
           token_str[ind]='\0';token_ind=ind;
          for(ind=0;ind<token_ind;++ind)
                if(!((*__ctype_b_loc ())[(int) ((token_str[ind]))] & (unsigned short int) _ISspace))
                      break;
          for(start=0;ind<=token_ind;++start,++ind)
                token_str[start]=token_str[ind];
          return 0;
}
