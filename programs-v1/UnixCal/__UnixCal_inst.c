
static char sccsid[] = "@(#)cal.c	4.4 (Berkeley) 87/05/28"; 
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
typedef __off_t off_t; 
typedef __pid_t pid_t; 
typedef __id_t id_t; 
typedef __ssize_t ssize_t; 
typedef __daddr_t daddr_t; 
typedef __caddr_t caddr_t; 
typedef __key_t key_t; 
typedef __clock_t clock_t; 
typedef __clockid_t clockid_t; 
typedef __time_t time_t; 
typedef __timer_t timer_t; 
typedef long unsigned int size_t; 
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
{ ponta_de_prova (3157, 1);
    return __builtin_bswap16 (__bsx); ponta_de_prova (3157, 2);
} 
static __uint32_t
__bswap_32 (__uint32_t __bsx) 
{ ponta_de_prova (3245, 1);
    return __builtin_bswap32 (__bsx); ponta_de_prova (3245, 2);
} 
static __uint64_t
__bswap_64 (__uint64_t __bsx) 
{ ponta_de_prova (3334, 1);
    return __builtin_bswap64 (__bsx); ponta_de_prova (3334, 2);
} 
static __uint16_t
__uint16_identity (__uint16_t __x) 
{ ponta_de_prova (3422, 1);
    return __x; ponta_de_prova (3422, 2);
} 
static __uint32_t
__uint32_identity (__uint32_t __x) 
{ ponta_de_prova (3493, 1);
    return __x; ponta_de_prova (3493, 2);
} 
static __uint64_t
__uint64_identity (__uint64_t __x) 
{ ponta_de_prova (3564, 1);
    return __x; ponta_de_prova (3564, 2);
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
struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
}; 
struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  }; 
struct sigevent; 
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
extern clock_t clock (void) ; 
extern time_t time (time_t *__timer) ; 
extern double difftime (time_t __time1, time_t __time0)
     ; 
extern time_t mktime (struct tm *__tp) ; 
extern size_t strftime (char * __s, size_t __maxsize,
   const char * __format,
   const struct tm * __tp)
   ; 
extern size_t strftime_l (char * __s, size_t __maxsize,
     const char * __format,
     const struct tm * __tp,
     locale_t __loc) ; 
extern struct tm *gmtime (const time_t *__timer) ; 
extern struct tm *localtime (const time_t *__timer) ; 
extern struct tm *gmtime_r (const time_t * __timer,
       struct tm * __tp) ; 
extern struct tm *localtime_r (const time_t * __timer,
          struct tm * __tp) ; 
extern char *asctime (const struct tm *__tp) ; 
extern char *ctime (const time_t *__timer) ; 
extern char *asctime_r (const struct tm * __tp,
   char * __buf) ; 
extern char *ctime_r (const time_t * __timer,
        char * __buf) ; 
extern char *__tzname[2]; 
extern int __daylight; 
extern long int __timezone; 
extern char *tzname[2]; 
extern void tzset (void) ; 
extern int daylight; 
extern long int timezone; 
extern time_t timegm (struct tm *__tp) ; 
extern time_t timelocal (struct tm *__tp) ; 
extern int dysize (int __year) ; 
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining); 
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) ; 
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp)
     ; 
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     ; 
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem); 
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) ; 
extern int timer_create (clockid_t __clock_id,
    struct sigevent * __evp,
    timer_t * __timerid) ; 
extern int timer_delete (timer_t __timerid) ; 
extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec * __value,
     struct itimerspec * __ovalue) ; 
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     ; 
extern int timer_getoverrun (timer_t __timerid) ; 
extern int timespec_get (struct timespec *__ts, int __base)
     ; 
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
char dayw[] = {
 " S  M Tu  W Th  F  S"
}; 
char *smon[] = {
 "January", "February", "March", "April",
 "May", "June", "July", "August",
 "September", "October", "November", "December",
}; 
char string[432]; 
void pstr(char *str, int n); 
void cal(int m, int y, char *p, int w); 
int jan1(int yr); 
void dispatch(int argc, char *argv[]) 
{ 
int y, i, j; 
int m; ponta_de_prova (25210, 1);
    if (argc == 2) {
        ponta_de_prova (25210, 2);goto xlong; }
    if  ( ponta_de_prova (25210, 3), (argc < 2) )
        { 
        time_t t; 
        struct tm *tm; 
            ponta_de_prova (25210, 4);
            t = time(((void *)0)); 
            tm = localtime(&t); 
            m = tm->tm_mon + 1; 
            y = tm->tm_year + 1900; 
        } 
    else 
        { 
            ponta_de_prova (25210, 5);
            m = atoi(argv[1]); 
            if (m < 1 || m > 12) 
                { 
                    ponta_de_prova (25210, 6);
                    fprintf(stderr, "cal: %s: Bad month.\n", argv[1]); 
                    exit(1); 
                } 
            ponta_de_prova (25210, 7);
            y = atoi(argv[2]); 
            if (y < 1 || y > 9999) 
                { 
                    ponta_de_prova (25210, 8);
                    fprintf(stderr, "cal: %s: Bad year.\n", argv[2]); 
                    exit(2); 
                } ponta_de_prova (25210, 9);
        } 
    ponta_de_prova (25210, 10);
    printf("   %s %u\n", smon[m - 1], y); 
    printf("%s\n", dayw); 
    cal(m, y, string, 24); 
    for ( i = 0; ponta_de_prova (25210, 11), i < 6 * 24; ponta_de_prova (25210, 12), i += 24  ){
        ponta_de_prova (25210, 13);
        pstr(string + i, 24); }
    ponta_de_prova (25210, 14);
    exit(0); 
    xlong: ponta_de_prova (25210, 15);
        y = atoi(argv[1]); 
    if (y < 1 || y > 9999) 
        { 
            ponta_de_prova (25210, 16);
            fprintf(stderr, "cal: %s: Bad year.\n", argv[1]); 
            exit(2); 
        } 
    ponta_de_prova (25210, 17);
    printf("\n\n\n"); 
    printf("				%u\n", y); 
    printf("\n"); 
    for ( i = 0; ponta_de_prova (25210, 18), i < 12; ponta_de_prova (25210, 19), i += 3  )
        { 
            for ( ponta_de_prova (25210, 20), j = 0; ponta_de_prova (25210, 21), j < 6 * 72; ponta_de_prova (25210, 22), j++  ){
                ponta_de_prova (25210, 23);
                string[j] = '\0'; }
            ponta_de_prova (25210, 24);
            printf("	 %.3s", smon[i]); 
            printf("			%.3s", smon[i + 1]); 
            printf("		       %.3s\n", smon[i + 2]); 
            printf("%s   %s   %s\n", dayw, dayw, dayw); 
            cal(i + 1, y, string, 72); 
            cal(i + 2, y, string + 23, 72); 
            cal(i + 3, y, string + 46, 72); 
            for ( j = 0; ponta_de_prova (25210, 25), j < 6 * 72; ponta_de_prova (25210, 26), j += 72  ){
                ponta_de_prova (25210, 27);
                pstr(string + j, 72); }ponta_de_prova (25210, 28);
        } 
    ponta_de_prova (25210, 29);
    printf("\n\n\n"); 
    exit(0); 
} 
void pstr(char *str, int n) 
{ 
int i; 
char *s; ponta_de_prova (26446, 1);
    s = str; 
    i = n; 
    
    while  ( ponta_de_prova (26446, 2), (i--) ){
        if  ( ponta_de_prova (26446, 3), (*s++ == '\0') ){
            ponta_de_prova (26446, 4);
            s[-1] = ' '; }}
    ponta_de_prova (26446, 6);
    i = n + 1; 
    
    while  ( ponta_de_prova (26446, 7), (i--) ){
        if  ( ponta_de_prova (26446, 8), (*--s != ' ') ){
            ponta_de_prova (26446, 9);
            break; }}
    ponta_de_prova (26446, 11);
    s[1] = '\0'; 
    printf("%s\n", str); 
} 
char mon[] = {
 0,
 31, 29, 31, 30,
 31, 30, 31, 31,
 30, 31, 30, 31,
}; 
void cal(int m, int y, char *p, int w) 
{ 
int d, i; 
char *s; ponta_de_prova (26726, 1);
    s = p; 
    d = jan1(y); 
    mon[2] = 29; 
    mon[9] = 30; 
    switch ((jan1(y + 1) + 7 - d) % 7) 
        { 
            case 1: ponta_de_prova (26726, 2);
                mon[2] = 28; 
            break; 
            default: ponta_de_prova (26726, 3);
                mon[9] = 19; 
            break; 
            case 2: ponta_de_prova (26726, 4);
                ; 
        } 
    for ( ponta_de_prova (26726, 5), i = 1; ponta_de_prova (26726, 6), i < m; ponta_de_prova (26726, 7), i++  ){
        ponta_de_prova (26726, 8);
        d += mon[i]; }
    ponta_de_prova (26726, 9);
    d %= 7; 
    s += 3 * d; 
    for ( i = 1; ponta_de_prova (26726, 10), i <= mon[m]; ponta_de_prova (26726, 11), i++  )
        { 
            if  ( ponta_de_prova (26726, 12), (i == 3 && mon[m] == 19) )
                { 
                    ponta_de_prova (26726, 13);
                    i += 11; 
                    mon[m] += 11; 
                } 
            if  ( ponta_de_prova (26726, 14), (i > 9) ){
                ponta_de_prova (26726, 15);
                *s = i / 10 + '0'; }
            ponta_de_prova (26726, 16);
            s++; 
            *s++ = i % 10 + '0'; 
            s++; 
            if (++d == 7) 
                { 
                    ponta_de_prova (26726, 17);
                    d = 0; 
                    s = p + w; 
                    p = s; 
                } ponta_de_prova (26726, 18);
        } ponta_de_prova (26726, 19);
} 
int jan1(int yr) 
{ 
int y, d; ponta_de_prova (27251, 1);
    y = yr; 
    d = 4 + y + (y + 3) / 4; 
    if (y > 1800) 
        { 
            ponta_de_prova (27251, 2);
            d -= (y - 1701) / 100; 
            d += (y - 1601) / 400; 
        } 
    if  ( ponta_de_prova (27251, 3), (y > 1752) ){
        ponta_de_prova (27251, 4);
        d += 3; }
    ponta_de_prova (27251, 5);
    return (d % 7); ponta_de_prova (27251, 6);
} 

