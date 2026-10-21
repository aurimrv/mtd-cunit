
typedef long unsigned int size_t; 
typedef __gnuc_va_list; 
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
{ ponta_de_prova (12262, 1);
    return __builtin_bswap16 (__bsx); ponta_de_prova (12262, 2);
} 
static __uint32_t
__bswap_32 (__uint32_t __bsx) 
{ ponta_de_prova (12350, 1);
    return __builtin_bswap32 (__bsx); ponta_de_prova (12350, 2);
} 
static __uint64_t
__bswap_64 (__uint64_t __bsx) 
{ ponta_de_prova (12439, 1);
    return __builtin_bswap64 (__bsx); ponta_de_prova (12439, 2);
} 
static __uint16_t
__uint16_identity (__uint16_t __x) 
{ ponta_de_prova (12527, 1);
    return __x; ponta_de_prova (12527, 2);
} 
static __uint32_t
__uint32_identity (__uint32_t __x) 
{ ponta_de_prova (12598, 1);
    return __x; ponta_de_prova (12598, 2);
} 
static __uint64_t
__uint64_identity (__uint64_t __x) 
{ ponta_de_prova (12669, 1);
    return __x; ponta_de_prova (12669, 2);
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
typedef
       FILE *character_stream; 
typedef
       int BOOLEAN; 
typedef
       char CHARACTER; 
typedef
       char *string; 
char get_char(character_stream fp); 
char unget_char(char ch, character_stream fp); 
character_stream open_character_stream(char *fname); 
typedef
    FILE *token_stream; 
typedef
    char *token; 
token_stream open_token_stream(char *fname); 
token get_token(token_stream tp); 
void print_token(token tok); 
int is_eof_token(token tok); 
int is_token_end(int str_com_id, char ch); 
int token_type(token tok); 
int is_comment(token ident); 
int is_keyword(token str); 
int is_char_constant(token str); 
int is_num_constant(token str); 
int is_str_constant(token str); 
int is_identifier(token str); 
int is_spec_symbol(token str); 
int unget_error(character_stream fp); 
void print_spec_symbol(token str); 
character_stream open_character_stream(char *fname) 
{ 
character_stream fp; ponta_de_prova (29365, 1);
    if (fname == ((void *)0)) {
        ponta_de_prova (29365, 2);
        fp=stdin; }
    else {
        if  ( ponta_de_prova (29365, 3), ((fp=fopen(fname,"r"))== ((void *)0)) )
            { 
                ponta_de_prova (29365, 4);
                fprintf(stdout, "The file %s doesn't exists\n",fname); 
                exit(0); 
            } }
    ponta_de_prova (29365, 6);
    return(fp); ponta_de_prova (29365, 7);
} 
char get_char(character_stream fp) 
{ 
char ch; ponta_de_prova (29620, 1);
    ch=getc(fp); 
    return(ch); ponta_de_prova (29620, 2);
} 
char unget_char(char ch, character_stream fp) 
{ 
char c; ponta_de_prova (29697, 1);
    c=ungetc(ch,fp); 
    if (c ==(-1)) 
        { 
            ponta_de_prova (29697, 2);
            return(c); ponta_de_prova (29697, 3);
        } 
    else {
        ponta_de_prova (29697, 4);
        return(c); }ponta_de_prova (29697, 5);
} 
char buffer[81]; 
int is_spec_symbol(token str); 
int is_token_end(int str_com_id, char ch); 
int unget_error(character_stream fp); 
int is_keyword(token str); 
int is_identifier(token str); 
int is_num_constant(token str); 
int is_char_constant(token str); 
int is_str_constant(token str); 
int is_comment(token ident); 
void print_spec_symbol(token str); 
token_stream open_token_stream(char *fname) 
{ 
token_stream fp; ponta_de_prova (30195, 1);
    if (strcmp(fname,"")==0) {
        ponta_de_prova (30195, 2);
        fp=open_character_stream(((void *)0)); }
    else {
        ponta_de_prova (30195, 3);
        fp=open_character_stream(fname); }
    ponta_de_prova (30195, 4);
    return(fp); ponta_de_prova (30195, 5);
} 
token get_token(token_stream tp) 
{ 
int i=0,j; 
int id=0; 
char ch,ch1[2]; ponta_de_prova (30378, 1);
    for ( j=0; ponta_de_prova (30378, 2), j<=80; ponta_de_prova (30378, 3), j++  )
        { 
            ponta_de_prova (30378, 4);
            buffer[j]='\0'; 
        } 
    ponta_de_prova (30378, 5);
    ch1[0]='\0'; 
    ch1[1]='\0'; 
    ch=get_char(tp); 
    
    while  ( ponta_de_prova (30378, 6), (ch==' '||ch=='\n') )
        { 
            ponta_de_prova (30378, 7);
            ch=get_char(tp); 
        } 
    ponta_de_prova (30378, 8);
    buffer[i]=ch; 
    if (is_eof_token(buffer)==1) {
        ponta_de_prova (30378, 9);
        return(buffer); }
    if  ( ponta_de_prova (30378, 10), (is_spec_symbol(buffer)==1) ){
        ponta_de_prova (30378, 11);
        return(buffer); }
    if  ( ponta_de_prova (30378, 12), (ch =='"') ){
        ponta_de_prova (30378, 13);
        id=1; }
    if  ( ponta_de_prova (30378, 14), (ch ==59) ){
        ponta_de_prova (30378, 15);
        id=2; }
    ponta_de_prova (30378, 16);
    ch=get_char(tp); 
    
    while  ( ponta_de_prova (30378, 17), (is_token_end(id,ch) == 0) )
        { 
            ponta_de_prova (30378, 18);
            i++; 
            buffer[i]=ch; 
            ch=get_char(tp); 
        } 
    ponta_de_prova (30378, 19);
    ch1[0]=ch; 
    if (is_eof_token(ch1)==1) 
        { 
            ponta_de_prova (30378, 20);
            ch=unget_char(ch,tp); 
            if (ch==(-1)) {
                ponta_de_prova (30378, 21);
                unget_error(tp); }
            ponta_de_prova (30378, 22);
            return(buffer); ponta_de_prova (30378, 23);
        } 
    if  ( ponta_de_prova (30378, 24), (is_spec_symbol(ch1)==1) )
        { 
            ponta_de_prova (30378, 25);
            ch=unget_char(ch,tp); 
            if (ch==(-1)) {
                ponta_de_prova (30378, 26);
                unget_error(tp); }
            ponta_de_prova (30378, 27);
            return(buffer); ponta_de_prova (30378, 28);
        } 
    if  ( ponta_de_prova (30378, 29), (id==1) )
        { 
            ponta_de_prova (30378, 30);
            i++; 
            buffer[i]=ch; 
            return(buffer); ponta_de_prova (30378, 31);
        } 
    if  ( ponta_de_prova (30378, 32), (id==0 && ch==59) )
        { 
            ponta_de_prova (30378, 33);
            ch=unget_char(ch,tp); 
            if (ch==(-1)) {
                ponta_de_prova (30378, 34);
                unget_error(tp); }
            ponta_de_prova (30378, 35);
            return(buffer); ponta_de_prova (30378, 36);
        } 
    ponta_de_prova (30378, 37);
    return(buffer); ponta_de_prova (30378, 38);
} 
int is_token_end(int str_com_id, char ch) 
{ 
char ch1[2]; ponta_de_prova (31380, 1);
    ch1[0]=ch; 
    ch1[1]='\0'; 
    if (is_eof_token(ch1)==1) {
        ponta_de_prova (31380, 2);
        return(1); }
    if  ( ponta_de_prova (31380, 3), (str_com_id==1) )
        { 
            if  ( ponta_de_prova (31380, 4), (ch=='"' | ch=='\n') ){
                ponta_de_prova (31380, 5);
                return(1); }
            else {
                ponta_de_prova (31380, 6);
                return(0); }ponta_de_prova (31380, 7);
        } 
    if  ( ponta_de_prova (31380, 8), (str_com_id==2) )
        { 
            if  ( ponta_de_prova (31380, 9), (ch=='\n') ){
                ponta_de_prova (31380, 10);
                return(1); }
            else {
                ponta_de_prova (31380, 11);
                return(0); }ponta_de_prova (31380, 12);
        } 
    if  ( ponta_de_prova (31380, 13), (is_spec_symbol(ch1)==1) ){
        ponta_de_prova (31380, 14);
        return(1); }
    if  ( ponta_de_prova (31380, 15), (ch ==' ' || ch=='\n' || ch==59) ){
        ponta_de_prova (31380, 16);
        return(1); }
    ponta_de_prova (31380, 17);
    return(0); ponta_de_prova (31380, 18);
} 
int token_type(token tok) 
{ ponta_de_prova (31795, 1);
    if (is_keyword(tok)) {
        ponta_de_prova (31795, 2);
        return(1); }
    if  ( ponta_de_prova (31795, 3), (is_spec_symbol(tok)) ){
        ponta_de_prova (31795, 4);
        return(2); }
    if  ( ponta_de_prova (31795, 5), (is_identifier(tok)) ){
        ponta_de_prova (31795, 6);
        return(3); }
    if  ( ponta_de_prova (31795, 7), (is_num_constant(tok)) ){
        ponta_de_prova (31795, 8);
        return(41); }
    if  ( ponta_de_prova (31795, 9), (is_str_constant(tok)) ){
        ponta_de_prova (31795, 10);
        return(42); }
    if  ( ponta_de_prova (31795, 11), (is_char_constant(tok)) ){
        ponta_de_prova (31795, 12);
        return(43); }
    if  ( ponta_de_prova (31795, 13), (is_comment(tok)) ){
        ponta_de_prova (31795, 14);
        return(5); }
    if  ( ponta_de_prova (31795, 15), (is_eof_token(tok)) ){
        ponta_de_prova (31795, 16);
        return(6); }
    ponta_de_prova (31795, 17);
    return(0); ponta_de_prova (31795, 18);
} 
void print_token(token tok) 
{ 
int type; ponta_de_prova (32114, 1);
    type=token_type(tok); 
    if (type==0) 
        { 
            ponta_de_prova (32114, 2);
            fprintf(stdout, "error,\"%s\".\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 3), (type==1) )
        { 
            ponta_de_prova (32114, 4);
            fprintf(stdout, "keyword,\"%s\".\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 5), (type==2) ){
        ponta_de_prova (32114, 6);
        print_spec_symbol(tok); }
    if  ( ponta_de_prova (32114, 7), (type==3) )
        { 
            ponta_de_prova (32114, 8);
            fprintf(stdout, "identifier,\"%s\".\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 9), (type==41) )
        { 
            ponta_de_prova (32114, 10);
            fprintf(stdout, "numeric,%s.\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 11), (type==42) )
        { 
            ponta_de_prova (32114, 12);
            fprintf(stdout, "string,%s.\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 13), (type==43) )
        { 
            ponta_de_prova (32114, 14);
            tok=tok+1; 
            fprintf(stdout, "character,\"%s\".\n",tok); 
        } 
    if  ( ponta_de_prova (32114, 15), (type==6) ){
        ponta_de_prova (32114, 16);
        fprintf(stdout, "eof.\n"); }ponta_de_prova (32114, 17);
} 
int is_eof_token(token tok) 
{ ponta_de_prova (32658, 1);
    if ( *tok==(-1)) {
        ponta_de_prova (32658, 2);
        return(1); }
    else {
        ponta_de_prova (32658, 3);
        return(0); }ponta_de_prova (32658, 4);
} 
int is_comment(token ident) 
{ ponta_de_prova (32749, 1);
    if ( (*ident) ==59 ) {
        ponta_de_prova (32749, 2);
        return(1); }
    else {
        ponta_de_prova (32749, 3);
        return(0); }ponta_de_prova (32749, 4);
} 
int is_keyword(token str) 
{ ponta_de_prova (32842, 1);
    if (!strcmp(str,"and") || !strcmp(str,"or") || !strcmp(str,"if") ||
    !strcmp(str,"xor")||!strcmp(str,"lambda")||!strcmp(str,"=>")) {
        ponta_de_prova (32842, 2);
        return(1); }
    else {
        ponta_de_prova (32842, 3);
        return(0); }ponta_de_prova (32842, 4);
} 
int is_char_constant(token str) 
{ ponta_de_prova (33048, 1);
    if ((*str)=='#' && ((*__ctype_b_loc ())[(int) ((*(str+1)))] & (unsigned short int) _ISalpha)) {
        ponta_de_prova (33048, 2);
        return(1); }
    else {
        ponta_de_prova (33048, 3);
        return(0); }ponta_de_prova (33048, 4);
} 
int is_num_constant(token str) 
{ 
int i=1; ponta_de_prova (33219, 1);
    if ( ((*__ctype_b_loc ())[(int) ((*str))] & (unsigned short int) _ISdigit)) 
        { 
            ponta_de_prova (33219, 2); 
            while  ( ponta_de_prova (33219, 3), ( *(str+i) != '\0' ) )
                { 
                    if  ( ponta_de_prova (33219, 4), (((*__ctype_b_loc ())[(int) ((*(str+i)))] & (unsigned short int) _ISdigit)) ){
                        ponta_de_prova (33219, 5);
                        i++; }
                    else {
                        ponta_de_prova (33219, 6);
                        return(0); }ponta_de_prova (33219, 7);
                } 
            ponta_de_prova (33219, 8);
            return(1); ponta_de_prova (33219, 9);
        } 
    else {
        ponta_de_prova (33219, 10);
        return(0); }ponta_de_prova (33219, 11);
} 
int is_str_constant(token str) 
{ 
int i=1; ponta_de_prova (33569, 1);
    if ( *str =='"') 
        { 
            ponta_de_prova (33569, 2); 
            while  ( ponta_de_prova (33569, 3), (*(str+i)!='\0') )
                { 
                    if  ( ponta_de_prova (33569, 4), (*(str+i)=='"') ){
                        ponta_de_prova (33569, 5);
                        return(1); }
                    else {
                        ponta_de_prova (33569, 6);
                        i++; }ponta_de_prova (33569, 7);
                } 
            ponta_de_prova (33569, 8);
            return(0); ponta_de_prova (33569, 9);
        } 
    else {
        ponta_de_prova (33569, 10);
        return(0); }ponta_de_prova (33569, 11);
} 
int is_identifier(token str) 
{ 
int i=1; ponta_de_prova (33804, 1);
    if ( ((*__ctype_b_loc ())[(int) ((*str))] & (unsigned short int) _ISalpha) ) 
        { 
            ponta_de_prova (33804, 2); 
            while  ( ponta_de_prova (33804, 3), ( *(str+i) !='\0' ) )
                { 
                    if  ( ponta_de_prova (33804, 4), (((*__ctype_b_loc ())[(int) ((*(str+i)))] & (unsigned short int) _ISalpha) || ((*__ctype_b_loc ())[(int) ((*(str+i)))] & (unsigned short int) _ISdigit)) ){
                        ponta_de_prova (33804, 5);
                        i++; }
                    else {
                        ponta_de_prova (33804, 6);
                        return(0); }ponta_de_prova (33804, 7);
                } 
            ponta_de_prova (33804, 8);
            return(1); ponta_de_prova (33804, 9);
        } 
    else {
        ponta_de_prova (33804, 10);
        return(0); }ponta_de_prova (33804, 11);
} 
int unget_error(character_stream fp) 
{ ponta_de_prova (34269, 1);
    fprintf(stdout,"It can not get charcter\n"); 
    return 0; ponta_de_prova (34269, 2);
} 
void print_spec_symbol(token str) 
{ ponta_de_prova (34370, 1);
    if (!strcmp(str,"(")) 
        { 
            ponta_de_prova (34370, 2);
            fprintf(stdout, "%s\n","lparen."); 
            return; ponta_de_prova (34370, 3);
        } 
    if  ( ponta_de_prova (34370, 4), (!strcmp(str,")")) )
        { 
            ponta_de_prova (34370, 5);
            fprintf(stdout, "%s\n","rparen."); 
            return; ponta_de_prova (34370, 6);
        } 
    if  ( ponta_de_prova (34370, 7), (!strcmp(str,"[")) )
        { 
            ponta_de_prova (34370, 8);
            fprintf(stdout, "%s\n","lsquare."); 
            return; ponta_de_prova (34370, 9);
        } 
    if  ( ponta_de_prova (34370, 10), (!strcmp(str,"]")) )
        { 
            ponta_de_prova (34370, 11);
            fprintf(stdout, "%s\n","rsquare."); 
            return; ponta_de_prova (34370, 12);
        } 
    if  ( ponta_de_prova (34370, 13), (!strcmp(str,"'")) )
        { 
            ponta_de_prova (34370, 14);
            fprintf(stdout, "%s\n","quote."); 
            return; ponta_de_prova (34370, 15);
        } 
    if  ( ponta_de_prova (34370, 16), (!strcmp(str,"`")) )
        { 
            ponta_de_prova (34370, 17);
            fprintf(stdout, "%s\n","bquote."); 
            return; ponta_de_prova (34370, 18);
        } 
    ponta_de_prova (34370, 19);
    fprintf(stdout, "%s\n","comma."); ponta_de_prova (34370, 20);
} 
int is_spec_symbol(token str) 
{ ponta_de_prova (35097, 1);
    if (!strcmp(str,"(")) 
        { 
            ponta_de_prova (35097, 2);
            return(1); ponta_de_prova (35097, 3);
        } 
    if  ( ponta_de_prova (35097, 4), (!strcmp(str,")")) )
        { 
            ponta_de_prova (35097, 5);
            return(1); ponta_de_prova (35097, 6);
        } 
    if  ( ponta_de_prova (35097, 7), (!strcmp(str,"[")) )
        { 
            ponta_de_prova (35097, 8);
            return(1); ponta_de_prova (35097, 9);
        } 
    if  ( ponta_de_prova (35097, 10), (!strcmp(str,"]")) )
        { 
            ponta_de_prova (35097, 11);
            return(1); ponta_de_prova (35097, 12);
        } 
    if  ( ponta_de_prova (35097, 13), (!strcmp(str,"'")) )
        { 
            ponta_de_prova (35097, 14);
            return(1); ponta_de_prova (35097, 15);
        } 
    if  ( ponta_de_prova (35097, 16), (!strcmp(str,"`")) )
        { 
            ponta_de_prova (35097, 17);
            return(1); ponta_de_prova (35097, 18);
        } 
    if  ( ponta_de_prova (35097, 19), (!strcmp(str,",")) )
        { 
            ponta_de_prova (35097, 20);
            return(1); ponta_de_prova (35097, 21);
        } 
    ponta_de_prova (35097, 22);
    return(0); ponta_de_prova (35097, 23);
} 

