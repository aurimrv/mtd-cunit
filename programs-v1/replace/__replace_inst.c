
extern void exit(); 
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
{ ponta_de_prova (14680, 1);
    return __builtin_bswap16 (__bsx); ponta_de_prova (14680, 2);
} 
static __uint32_t
__bswap_32 (__uint32_t __bsx) 
{ ponta_de_prova (14768, 1);
    return __builtin_bswap32 (__bsx); ponta_de_prova (14768, 2);
} 
static __uint64_t
__bswap_64 (__uint64_t __bsx) 
{ ponta_de_prova (14857, 1);
    return __builtin_bswap64 (__bsx); ponta_de_prova (14857, 2);
} 
static __uint16_t
__uint16_identity (__uint16_t __x) 
{ ponta_de_prova (14945, 1);
    return __x; ponta_de_prova (14945, 2);
} 
static __uint32_t
__uint32_identity (__uint32_t __x) 
{ ponta_de_prova (15016, 1);
    return __x; ponta_de_prova (15016, 2);
} 
static __uint64_t
__uint64_identity (__uint64_t __x) 
{ ponta_de_prova (15087, 1);
    return __x; ponta_de_prova (15087, 2);
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
void Caseerror(int n); 
typedef char bool; 
typedef char character; 
typedef char string[100]; 
bool get_line(char *s, int maxsize) 
{ 
char *result; ponta_de_prova (24567, 1);
    result = fgets(s, maxsize, stdin); 
    return (result != ((void *)0)); ponta_de_prova (24567, 2);
} 
int addstr(char c, char *outset, int *j, int maxset) 
{ 
bool result; ponta_de_prova (24699, 1);
    if (*j >= maxset) {
        ponta_de_prova (24699, 2);
        result = 0; }
    else 
        { 
            ponta_de_prova (24699, 3);
            outset[*j] = c; 
            *j = *j + 1; 
            result = 1; 
        } 
    ponta_de_prova (24699, 4);
    return result; ponta_de_prova (24699, 5);
} 
char esc(char *s, int *i) 
{ 
char result; ponta_de_prova (24889, 1);
    if (s[*i] != '@') {
        ponta_de_prova (24889, 2);
        result = s[*i]; }
    else {
        if  ( ponta_de_prova (24889, 3), (s[*i + 1] == '\0') ){
            ponta_de_prova (24889, 4);
            result = '@'; }
        else 
            { 
                ponta_de_prova (24889, 5);
                *i = *i + 1; 
                if (s[*i] == 'n') {
                    ponta_de_prova (24889, 6);
                    result = 10; }
                else {
                    if  ( ponta_de_prova (24889, 7), (s[*i] == 't') ){
                        ponta_de_prova (24889, 8);
                        result = 9; }
                    else {
                        ponta_de_prova (24889, 9);
                        result = s[*i]; }}ponta_de_prova (24889, 11);
            } }
    ponta_de_prova (24889, 13);
    return result; ponta_de_prova (24889, 14);
} 
void change(char *pat, char *sub); 
void dodash(char delim, char *src, int *i, char *dest, int *j, int maxset) 
{ 
int k; 
bool junk; 
char escjunk; ponta_de_prova (25226, 1);
    
    while  ( ponta_de_prova (25226, 2), ((src[*i] != delim) && (src[*i] != '\0')) )
        { 
            if  ( ponta_de_prova (25226, 3), (src[*i - 1] == '@') )
                { 
                    ponta_de_prova (25226, 4);
                    escjunk = esc(src, i); 
                    junk = addstr(escjunk, dest, j, maxset); 
                } 
            else {
                if  ( ponta_de_prova (25226, 5), (src[*i] != '-') ){
                    ponta_de_prova (25226, 6);
                    junk = addstr(src[*i], dest, j, maxset); }
                else {
                    if  ( ponta_de_prova (25226, 7), (*j <= 1 || src[*i + 1] == '\0') ){
                        ponta_de_prova (25226, 8);
                        junk = addstr('-', dest, j, maxset); }
                    else {
                        if  ( ponta_de_prova (25226, 9), ((((*__ctype_b_loc ())[(int) ((src[*i - 1]))] & (unsigned short int) _ISalnum)) && (((*__ctype_b_loc ())[(int) ((src[*i + 1]))] & (unsigned short int) _ISalnum))
  && (src[*i - 1] <= src[*i + 1])) )
                            { 
                                for ( ponta_de_prova (25226, 10), k = src[*i-1]+1; ponta_de_prova (25226, 11), k<=src[*i+1]; ponta_de_prova (25226, 12), k++  )
                                    { 
                                        ponta_de_prova (25226, 13);
                                        junk = addstr(k, dest, j, maxset); 
                                    } 
                                ponta_de_prova (25226, 14);
                                *i = *i + 1; 
                            } 
                        else {
                            ponta_de_prova (25226, 15);
                            junk = addstr('-', dest, j, maxset); }}}}
            ponta_de_prova (25226, 19);
            (*i) = (*i) + 1; 
        } ponta_de_prova (25226, 20);
} 
bool getccl(char *arg, int *i, char *pat, int *j) 
{ 
int jstart; 
bool junk; ponta_de_prova (26080, 1);
    *i = *i + 1; 
    if (arg[*i] == '^') 
        { 
            ponta_de_prova (26080, 2);
            junk = addstr('!', pat, j, 100); 
            *i = *i + 1; 
        } 
    else {
        ponta_de_prova (26080, 3);
        junk = addstr('[', pat, j, 100); }
    ponta_de_prova (26080, 4);
    jstart = *j; 
    junk = addstr(0, pat, j, 100); 
    dodash(']', arg, i, pat, j, 100); 
    pat[jstart] = *j - jstart - 1; 
    return (arg[*i] == ']'); ponta_de_prova (26080, 5);
} 
void stclose(char *pat, int *j, int lastj) 
{ 
int jt; 
int jp; 
bool junk; ponta_de_prova (26455, 1);
    for ( jp = *j - 1; ponta_de_prova (26455, 2), jp >= lastj ; ponta_de_prova (26455, 3), jp--  )
        { 
            ponta_de_prova (26455, 4);
            jt = jp + 1; 
            junk = addstr(pat[jp], pat, &jt, 100); 
        } 
    ponta_de_prova (26455, 5);
    *j = *j + 1; 
    pat[lastj] = '*'; 
} 
bool in_set_2(char c) 
{ ponta_de_prova (26688, 1);
    return (c == '%' || c == '$' || c == '*'); ponta_de_prova (26688, 2);
} 
bool in_pat_set(char c) 
{ ponta_de_prova (26759, 1);
    return ( c == 'c' || c == '%' || c == '$' || c == '?'
          || c == '[' || c == '!' || c == '*'); ponta_de_prova (26759, 2);
} 
int makepat(char *arg, int start, char delim, char *pat) 
{ 
int result; 
int i, j, lastj, lj; 
bool done, junk; 
bool getres; 
char escjunk; ponta_de_prova (26890, 1);
    j = 0; 
    i = start; 
    lastj = 0; 
    done = 0; 
    
    while  ( ponta_de_prova (26890, 2), ((!done) && (arg[i] != delim) && (arg[i] != '\0')) )
        { 
            ponta_de_prova (26890, 3);
            lj = j; 
            if ((arg[i] == '?')) {
                ponta_de_prova (26890, 4);
                junk = addstr('?', pat, &j, 100); }
            else {
                if  ( ponta_de_prova (26890, 5), ((arg[i] == '%') && (i == start)) ){
                    ponta_de_prova (26890, 6);
                    junk = addstr('%', pat, &j, 100); }
                else {
                    if  ( ponta_de_prova (26890, 7), ((arg[i] == '$') && (arg[i+1] == delim)) ){
                        ponta_de_prova (26890, 8);
                        junk = addstr('$', pat, &j, 100); }
                    else {
                        if  ( ponta_de_prova (26890, 9), ((arg[i] == '[')) )
                            { 
                                ponta_de_prova (26890, 10);
                                getres = getccl(arg, &i, pat, &j); 
                                done = (bool)(getres == 0); 
                            } 
                        else {
                            if  ( ponta_de_prova (26890, 11), ((arg[i] == '*') && (i > start)) )
                                { 
                                    ponta_de_prova (26890, 12);
                                    lj = lastj; 
                                    if (in_set_2(pat[lj])) {
                                        ponta_de_prova (26890, 13);
                                        done = 1; }
                                    else {
                                        ponta_de_prova (26890, 14);
                                        stclose(pat, &j, lastj); }ponta_de_prova (26890, 15);
                                } 
                            else 
                                { 
                                    ponta_de_prova (26890, 16);
                                    junk = addstr('c', pat, &j, 100); 
                                    escjunk = esc(arg, &i); 
                                    junk = addstr(escjunk, pat, &j, 100); 
                                } }}}}
            ponta_de_prova (26890, 21);
            lastj = lj; 
            if ((!done)) {
                ponta_de_prova (26890, 22);
                i = i + 1; }ponta_de_prova (26890, 23);
        } 
    ponta_de_prova (26890, 24);
    junk = addstr('\0', pat, &j, 100); 
    if ((done) || (arg[i] != delim)) {
        ponta_de_prova (26890, 25);
        result = 0; }
    else {
        if  ( ponta_de_prova (26890, 26), ((!junk)) ){
            ponta_de_prova (26890, 27);
            result = 0; }
        else {
            ponta_de_prova (26890, 28);
            result = i; }}
    ponta_de_prova (26890, 30);
    return result; ponta_de_prova (26890, 31);
} 
int getpat(char *arg, char *pat) 
{ 
int makeres; ponta_de_prova (27998, 1);
    makeres = makepat(arg, 0, '\0', pat); 
    return (makeres > 0); ponta_de_prova (27998, 2);
} 
int makesub(char *arg, int from, character delim, char *sub) 
{ 
int result; 
int i, j; 
bool junk; 
character escjunk; ponta_de_prova (28120, 1);
    j = 0; 
    i = from; 
    
    while  ( ponta_de_prova (28120, 2), ((arg[i] != delim) && (arg[i] != '\0')) )
        { 
            if  ( ponta_de_prova (28120, 3), ((arg[i] == (unsigned)('&'))) ){
                ponta_de_prova (28120, 4);
                junk = addstr(-1, sub, &j, 100); }
            else 
                { 
                    ponta_de_prova (28120, 5);
                    escjunk = esc(arg, &i); 
                    junk = addstr(escjunk, sub, &j, 100); 
                } 
            ponta_de_prova (28120, 6);
            i = i + 1; 
        } 
    if  ( ponta_de_prova (28120, 7), (arg[i] != delim) ){
        ponta_de_prova (28120, 8);
        result = 0; }
    else 
        { 
            ponta_de_prova (28120, 9);
            junk = addstr('\0', &(*sub), &j, 100); 
            if ((!junk)) {
                ponta_de_prova (28120, 10);
                result = 0; }
            else {
                ponta_de_prova (28120, 11);
                result = i; }ponta_de_prova (28120, 12);
        } 
    ponta_de_prova (28120, 13);
    return result; ponta_de_prova (28120, 14);
} 
bool getsub(char *arg, char *sub) 
{ 
int makeres; ponta_de_prova (28672, 1);
    makeres = makesub(arg, 0, '\0', sub); 
    return (makeres > 0); ponta_de_prova (28672, 2);
} 
void subline(char *lin, char *pat, char *sub); 
bool locate(character c, char *pat, int offset) 
{ 
int i; 
bool flag; ponta_de_prova (28842, 1);
    flag = 0; 
    i = offset + pat[offset]; 
    
    while  ( ponta_de_prova (28842, 2), ((i > offset)) )
        { 
            if  ( ponta_de_prova (28842, 3), (c == pat[i]) )
                { 
                    ponta_de_prova (28842, 4);
                    flag = 1; 
                    i = offset; 
                } 
            else {
                ponta_de_prova (28842, 5);
                i = i - 1; }ponta_de_prova (28842, 6);
        } 
    ponta_de_prova (28842, 7);
    return flag; ponta_de_prova (28842, 8);
} 
bool omatch(char *lin, int *i, char *pat, int j) 
{ 
char advance; 
bool result; ponta_de_prova (29094, 1);
    advance = -1; 
    if ((lin[*i] == '\0')) {
        ponta_de_prova (29094, 2);
        result = 0; }
    else 
        { 
            if  ( ponta_de_prova (29094, 3), (!in_pat_set(pat[j])) )
                { 
                    ponta_de_prova (29094, 4);
                    (void)fprintf(stdout, "in omatch: can't happen\n"); 
                    abort(); 
                } 
            else 
                { 
                    switch  ( ponta_de_prova (29094, 5), (pat[j]) )
                        { 
                            case 'c': ponta_de_prova (29094, 6);
                                if (lin[*i] == pat[j + 1]) {
                                    ponta_de_prova (29094, 7);
                                    advance = 1; }
                            ponta_de_prova (29094, 8);
                            break ; 
                            case '%': ponta_de_prova (29094, 9);
                                if (*i == 0) {
                                    ponta_de_prova (29094, 10);
                                    advance = 0; }
                            ponta_de_prova (29094, 11);
                            break ; 
                            case '?': ponta_de_prova (29094, 12);
                                if (lin[*i] != 10) {
                                    ponta_de_prova (29094, 13);
                                    advance = 1; }
                            ponta_de_prova (29094, 14);
                            break ; 
                            case '$': ponta_de_prova (29094, 15);
                                if (lin[*i] == 10) {
                                    ponta_de_prova (29094, 16);
                                    advance = 0; }
                            ponta_de_prova (29094, 17);
                            break ; 
                            case '[': ponta_de_prova (29094, 18);
                                if (locate(lin[*i], pat, j + 1)) {
                                    ponta_de_prova (29094, 19);
                                    advance = 1; }
                            ponta_de_prova (29094, 20);
                            break ; 
                            case '!': ponta_de_prova (29094, 21);
                                if ((lin[*i] != 10) && (!locate(lin[*i], pat, j+1))) {
                                    ponta_de_prova (29094, 22);
                                    advance = 1; }
                            ponta_de_prova (29094, 23);
                            break ; 
                            default: ponta_de_prova (29094, 24);
                                Caseerror(pat[j]); 
                        } 
                    ponta_de_prova (29094, 25);
                    ; 
                } ponta_de_prova (29094, 26);
        } 
    if  ( ponta_de_prova (29094, 27), ((advance >= 0)) )
        { 
            ponta_de_prova (29094, 28);
            *i = *i + advance; 
            result = 1; 
        } 
    else {
        ponta_de_prova (29094, 29);
        result = 0; }
    ponta_de_prova (29094, 30);
    return result; ponta_de_prova (29094, 31);
} 
int patsize(char *pat, int n) 
{ 
int size; ponta_de_prova (30021, 1);
    if (!in_pat_set(pat[n])) 
        { 
            ponta_de_prova (30021, 2);
            (void)fprintf(stdout, "in patsize: can't happen\n"); 
            abort(); 
        } 
    else {
        switch  ( ponta_de_prova (30021, 3), (pat[n]) )
            { 
                case 'c': ponta_de_prova (30021, 4);
                    size = 2; 
                break; 
                case '%': ponta_de_prova (30021, 5);
                    case '$': ponta_de_prova (30021, 6);
                        case '?': ponta_de_prova (30021, 6);
                            size = 1; 
                break; 
                case '[': ponta_de_prova (30021, 7);
                    case '!': ponta_de_prova (30021, 8);
                        size = pat[n + 1] + 2; 
                break ; 
                case '*': ponta_de_prova (30021, 9);
                    size = 1; 
                break ; 
                default: ponta_de_prova (30021, 10);
                    Caseerror(pat[n]); 
            } }
    ponta_de_prova (30021, 12);
    return size; ponta_de_prova (30021, 13);
} 
int amatch(char *lin, int offset, char *pat, int j) 
{ 
int i, k; 
bool result, done; ponta_de_prova (30436, 1);
    done = 0; 
    
    while  ( ponta_de_prova (30436, 2), ((!done) && (pat[j] != '\0')) ){
        if  ( ponta_de_prova (30436, 3), ((pat[j] == '*')) )
            { 
                ponta_de_prova (30436, 4);
                j = j + patsize(pat, j); 
                i = offset; 
                
                while  ( ponta_de_prova (30436, 5), ((!done) && (lin[i] != '\0')) )
                    { 
                        ponta_de_prova (30436, 6);
                        result = omatch(lin, &i, pat, j); 
                        if (!result) {
                            ponta_de_prova (30436, 7);
                            done = 1; }ponta_de_prova (30436, 8);
                    } 
                ponta_de_prova (30436, 9);
                done = 0; 
                
                while  ( ponta_de_prova (30436, 10), ((!done) && (i >= offset)) )
                    { 
                        ponta_de_prova (30436, 11);
                        k = amatch(lin, i, pat, j + patsize(pat, j)); 
                        if ((k >= 0)) {
                            ponta_de_prova (30436, 12);
                            done = 1; }
                        else {
                            ponta_de_prova (30436, 13);
                            i = i - 1; }ponta_de_prova (30436, 14);
                    } 
                ponta_de_prova (30436, 15);
                offset = k; 
                done = 1; 
            } 
        else 
            { 
                ponta_de_prova (30436, 16);
                result = omatch(lin, &offset, pat, j); 
                if ((!result)) 
                    { 
                        ponta_de_prova (30436, 17);
                        offset = -1; 
                        done = 1; 
                    } 
                else {
                    ponta_de_prova (30436, 18);
                    j = j + patsize(pat, j); }ponta_de_prova (30436, 19);
            } }
    ponta_de_prova (30436, 21);
    return offset; ponta_de_prova (30436, 22);
} 
void putsub(char *lin, int s1, int s2, char *sub) 
{ 
int i; 
int j; ponta_de_prova (31135, 1);
    i = 0; 
    
    while  ( ponta_de_prova (31135, 2), ((sub[i] != '\0')) )
        { 
            if  ( ponta_de_prova (31135, 3), ((sub[i] == -1)) ){
                for ( ponta_de_prova (31135, 4), j = s1; ponta_de_prova (31135, 5), j < s2; ponta_de_prova (31135, 6), j++  )
                    { 
                        ponta_de_prova (31135, 7);
                        fputc(lin[j],stdout); 
                    } }
            else 
                { 
                    ponta_de_prova (31135, 9);
                    fputc(sub[i],stdout); 
                } 
            ponta_de_prova (31135, 10);
            i = i + 1; 
        } ponta_de_prova (31135, 11);
} 
void subline(char *lin, char *pat, char *sub) 
{ 
int i, lastm, m; ponta_de_prova (31400, 1);
    lastm = -1; 
    i = 0; 
    
    while  ( ponta_de_prova (31400, 2), ((lin[i] != '\0')) )
        { 
            ponta_de_prova (31400, 3);
            m = amatch(lin, i, pat, 0); 
            if ((m >= 0) && (lastm != m)) 
                { 
                    ponta_de_prova (31400, 4);
                    putsub(lin, i, m, sub); 
                    lastm = m; 
                } 
            if  ( ponta_de_prova (31400, 5), ((m == -1) || (m == i)) )
                { 
                    ponta_de_prova (31400, 6);
                    fputc(lin[i],stdout); 
                    i = i + 1; 
                } 
            else {
                ponta_de_prova (31400, 7);
                i = m; }ponta_de_prova (31400, 8);
        } ponta_de_prova (31400, 9);
} 
void change(char *pat, char *sub) 
{ 
string line; 
bool result; ponta_de_prova (31729, 1);
    result = get_line(line, 100); 
    
    while  ( ponta_de_prova (31729, 2), ((result)) )
        { 
            ponta_de_prova (31729, 3);
            subline(line, pat, sub); 
            result = get_line(line, 100); 
        } ponta_de_prova (31729, 4);
} 
void Caseerror(int n) 
{ ponta_de_prova (31921, 1);
    (void)fprintf(stdout, "Missing case limb: line %d\n", n); 
    exit(4); 
} 

