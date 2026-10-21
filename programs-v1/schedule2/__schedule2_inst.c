
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
typedef long int ptrdiff_t; 
typedef int wchar_t; 
typedef struct {
  long long __max_align_ll ;
  long double __max_align_ld ;
} max_align_t; 
extern void *malloc (size_t __size)
     ; 
extern void *calloc (size_t __nmemb, size_t __size)
 ; 
extern void *realloc (void *__ptr, size_t __size)
 ; 
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
 
  ; 
extern void free (void *__ptr) ; 
extern void *memalign (size_t __alignment, size_t __size)
 
  ; 
extern void *valloc (size_t __size)
     ; 
extern void *pvalloc (size_t __size)
  ; 
struct mallinfo
{
  int arena;
  int ordblks;
  int smblks;
  int hblks;
  int hblkhd;
  int usmblks;
  int fsmblks;
  int uordblks;
  int fordblks;
  int keepcost;
}; 
struct mallinfo2
{
  size_t arena;
  size_t ordblks;
  size_t smblks;
  size_t hblks;
  size_t hblkhd;
  size_t usmblks;
  size_t fsmblks;
  size_t uordblks;
  size_t fordblks;
  size_t keepcost;
}; 
extern struct mallinfo mallinfo (void) ; 
extern struct mallinfo2 mallinfo2 (void) ; 
extern int mallopt (int __param, int __val) ; 
extern int malloc_trim (size_t __pad) ; 
extern size_t malloc_usable_size (void *__ptr) ; 
extern void malloc_stats (void) ; 
extern int malloc_info (int __options, FILE *__fp) ; 
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
{ ponta_de_prova (17816, 1);
    return __builtin_bswap16 (__bsx); ponta_de_prova (17816, 2);
} 
static __uint32_t
__bswap_32 (__uint32_t __bsx) 
{ ponta_de_prova (17904, 1);
    return __builtin_bswap32 (__bsx); ponta_de_prova (17904, 2);
} 
static __uint64_t
__bswap_64 (__uint64_t __bsx) 
{ ponta_de_prova (17993, 1);
    return __builtin_bswap64 (__bsx); ponta_de_prova (17993, 2);
} 
static __uint16_t
__uint16_identity (__uint16_t __x) 
{ ponta_de_prova (18081, 1);
    return __x; ponta_de_prova (18081, 2);
} 
static __uint32_t
__uint32_identity (__uint32_t __x) 
{ ponta_de_prova (18152, 1);
    return __x; ponta_de_prova (18152, 2);
} 
static __uint64_t
__uint64_identity (__uint64_t __x) 
{ ponta_de_prova (18223, 1);
    return __x; ponta_de_prova (18223, 2);
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
struct process
{
    unsigned int pid;
    int priority;
    struct process *next;
}; 
extern int get_command(int *command, int *prio, float *ratio); 
extern void exit_here(int status); 
extern int enqueue(int prio, struct process *new_process); 
extern int new_job(int prio); 
extern int schedule(int command, int prio, float ratio); 
extern struct process *get_current(void); 
extern int reschedule(int prio); 
extern int put_end(int prio, struct process *process); 
extern int get_process(int prio, float ratio, struct process **job); 
extern void dispatch(void); 
extern int upgrade_prio(int prio, float ratio); 
extern int block(void); 
extern int unblock(float ratio); 
extern int quantum_expire(void); 
extern int finish(void); 
extern int flush(void); 
static struct process *current_job; 
static int next_pid = 0; 
FILE *mystdin; 
int enqueue(int prio, struct process *new_process) 
{ 
int status; ponta_de_prova (28430, 1);
    if (status = put_end(prio, new_process)) {
        ponta_de_prova (28430, 2);
        return (status); }
    ponta_de_prova (28430, 3);
    return (reschedule(prio)); ponta_de_prova (28430, 4);
} 
struct queue {
 int length;
 struct process *head;
}; 
static struct queue prio_queue[3 + 1]; 
void dispatch(void) 
{ 
int command, prio, status; 
float ratio; 
struct process *process; ponta_de_prova (28681, 1);
    
    while  ( ponta_de_prova (28681, 2), ((status = get_command(&command, &prio, &ratio)) > 0) )
        { 
            ponta_de_prova (28681, 3);
            schedule(command, prio, ratio); 
        } 
    if  ( ponta_de_prova (28681, 4), (status < 0) ){
        ponta_de_prova (28681, 5);
        exit_here(status); }
    ponta_de_prova (28681, 6);
    exit_here(0); 
} 
int get_command(int *command, int *prio, float *ratio) 
{ 
int status = 0; 
char buf[20]; ponta_de_prova (28925, 1);
    if (fgets(buf, 20, mystdin)) 
        { 
            ponta_de_prova (28925, 2);
            *prio = *command = -1; 
            *ratio = -1.0; 
            sscanf(buf, "%d", command); 
            switch (*command) 
                { 
                    case 1: ponta_de_prova (28925, 3);
                        sscanf(buf, "%*s%d", prio); 
                    break; 
                    case 4: ponta_de_prova (28925, 4);
                        sscanf(buf, "%*s%f", ratio); 
                    break; 
                    case 2: ponta_de_prova (28925, 5);
                        sscanf(buf, "%*s%d%f", prio, ratio); 
                    break; ponta_de_prova (28925, 6);
                } 
            ponta_de_prova (28925, 7); 
            while  ( ponta_de_prova (28925, 8), (buf[strlen(buf) - 1] != '\n'
         && fgets(buf, 20, mystdin)) ){
                ponta_de_prova (28925, 9);
                ; }
            ponta_de_prova (28925, 10);
            return (1); ponta_de_prova (28925, 11);
        } 
    else {
        ponta_de_prova (28925, 12);
        return (0); }ponta_de_prova (28925, 13);
} 
void exit_here(int status) 
{ ponta_de_prova (29423, 1);
    exit(abs(status)); 
} 
int new_job(int prio) 
{ 
int pid, status = 0; 
struct process *new_process; ponta_de_prova (29473, 1);
    pid = next_pid++; 
    new_process = (struct process *)malloc(sizeof(struct process)); 
    if (!new_process) {
        ponta_de_prova (29473, 2);
        status = -3; }
    else 
        { 
            ponta_de_prova (29473, 3);
            new_process->pid = pid; 
            new_process->priority = prio; 
            new_process->next = (struct process *)0; 
            status = enqueue(prio, new_process); 
            if (status) 
                { 
                    ponta_de_prova (29473, 4);
                    free(new_process); 
                } ponta_de_prova (29473, 5);
        } 
    if  ( ponta_de_prova (29473, 6), (status) ){
        ponta_de_prova (29473, 7);
        next_pid--; }
    ponta_de_prova (29473, 8);
    return (status); ponta_de_prova (29473, 9);
} 
int upgrade_prio(int prio, float ratio) 
{ 
int status; 
struct process *job; ponta_de_prova (29907, 1);
    if (prio < 1 || prio > 2) {
        ponta_de_prova (29907, 2);
        return (-4); }
    if  ( ponta_de_prova (29907, 3), ((status = get_process(prio, ratio, &job)) <= 0) ){
        ponta_de_prova (29907, 4);
        return (status); }
    ponta_de_prova (29907, 5);
    job->priority = prio + 1; 
    return (enqueue(prio + 1, job)); ponta_de_prova (29907, 6);
} 
int block(void) 
{ 
struct process *job; ponta_de_prova (30161, 1);
    job = get_current(); 
    if (job) 
        { 
            ponta_de_prova (30161, 2);
            current_job = (struct process *)0; 
            return (enqueue(0, job)); ponta_de_prova (30161, 3);
        } 
    ponta_de_prova (30161, 4);
    return (0); ponta_de_prova (30161, 5);
} 
int unblock(float ratio) 
{ 
int status; 
struct process *job; ponta_de_prova (30318, 1);
    if ((status = get_process(0, ratio, &job)) <= 0) {
        ponta_de_prova (30318, 2);
        return (status); }
    ponta_de_prova (30318, 3);
    return (enqueue(job->priority, job)); ponta_de_prova (30318, 4);
} 
int quantum_expire(void) 
{ 
struct process *job; ponta_de_prova (30490, 1);
    job = get_current(); 
    if (job) 
        { 
            ponta_de_prova (30490, 2);
            current_job = (struct process *)0; 
            return (enqueue(job->priority, job)); ponta_de_prova (30490, 3);
        } 
    ponta_de_prova (30490, 4);
    return (0); ponta_de_prova (30490, 5);
} 
int finish(void) 
{ 
struct process *job; ponta_de_prova (30668, 1);
    job = get_current(); 
    if (job) 
        { 
            ponta_de_prova (30668, 2);
            current_job = (struct process *)0; 
            reschedule(0); 
            fprintf(stdout, " %d", job->pid); 
            free(job); 
            return (0); ponta_de_prova (30668, 3);
        } 
    else {
        ponta_de_prova (30668, 4);
        return (1); }ponta_de_prova (30668, 5);
} 
int flush(void) 
{ ponta_de_prova (30884, 1);
    
    while  ( ponta_de_prova (30884, 2), (!finish()) ){
        ponta_de_prova (30884, 3);
        ; }
    ponta_de_prova (30884, 4);
    fprintf(stdout, "\n"); 
    return (0); ponta_de_prova (30884, 5);
} 
struct process *get_current(void) 
{ 
int prio; ponta_de_prova (30974, 1);
    if (!current_job) 
        { 
            for ( ponta_de_prova (30974, 2), prio = 3; ponta_de_prova (30974, 3), prio > 0; ponta_de_prova (30974, 4), prio--  )
                { 
                    if  ( ponta_de_prova (30974, 5), (get_process(prio, 0.0, &current_job) > 0) ){
                        ponta_de_prova (30974, 6);
                        break; }ponta_de_prova (30974, 7);
                } ponta_de_prova (30974, 8);
        } 
    ponta_de_prova (30974, 9);
    return (current_job); ponta_de_prova (30974, 10);
} 
int reschedule(int prio) 
{ ponta_de_prova (31159, 1);
    if (current_job && prio > current_job->priority) 
        { 
            ponta_de_prova (31159, 2);
            put_end(current_job->priority, current_job); 
            current_job = (struct process *)0; 
        } 
    ponta_de_prova (31159, 3);
    get_current(); 
    return (0); ponta_de_prova (31159, 4);
} 
int schedule(int command, int prio, float ratio) 
{ 
int status = 0; ponta_de_prova (31356, 1);
    switch (command) 
        { 
            case 1: ponta_de_prova (31356, 2);
                status = new_job(prio); 
            break; 
            case 5: ponta_de_prova (31356, 3);
                status = quantum_expire(); 
            break; 
            case 2: ponta_de_prova (31356, 4);
                status = upgrade_prio(prio, ratio); 
            break; 
            case 3: ponta_de_prova (31356, 5);
                status = block(); 
            break; 
            case 4: ponta_de_prova (31356, 6);
                status = unblock(ratio); 
            break; 
            case 6: ponta_de_prova (31356, 7);
                finish(); 
            fprintf(stdout, "\n"); 
            break; 
            case 7: ponta_de_prova (31356, 8);
                status = flush(); 
            break; 
            default: ponta_de_prova (31356, 9);
                status = -6; 
        } 
    ponta_de_prova (31356, 10);
    return (status); ponta_de_prova (31356, 11);
} 
int put_end(int prio, struct process *process) 
{ 
struct process **next; ponta_de_prova (31815, 1);
    if (prio > 3 || prio < 0) {
        ponta_de_prova (31815, 2);
        return (-4); }
    for ( ponta_de_prova (31815, 3), next = &prio_queue[prio].head; ponta_de_prova (31815, 4), *next; ponta_de_prova (31815, 5), next = &(*next)->next  ){
        ponta_de_prova (31815, 6);
        ; }
    ponta_de_prova (31815, 7);
    *next = process; 
    prio_queue[prio].length++; 
    return (0); ponta_de_prova (31815, 8);
} 
int get_process(int prio, float ratio, struct process **job) 
{ 
int length, index; 
struct process **next; ponta_de_prova (32060, 1);
    if (prio > 3 || prio < 0) {
        ponta_de_prova (32060, 2);
        return (-4); }
    if  ( ponta_de_prova (32060, 3), (ratio < 0.0 || ratio > 1.0) ){
        ponta_de_prova (32060, 4);
        return (-5); }
    ponta_de_prova (32060, 5);
    length = prio_queue[prio].length; 
    index = ratio * length; 
    index = index >= length ? length - 1 : index; 
    for ( next = &prio_queue[prio].head; ponta_de_prova (32060, 6), index && *next; ponta_de_prova (32060, 7), index--  ){
        ponta_de_prova (32060, 8);
        next = &(*next)->next; }
    ponta_de_prova (32060, 9);
    *job = *next; 
    if (*job) 
        { 
            ponta_de_prova (32060, 10);
            *next = (*next)->next; 
            (*job)->next = (struct process *)0; 
            prio_queue[prio].length--; 
            return (1); ponta_de_prova (32060, 11);
        } 
    else {
        ponta_de_prova (32060, 12);
        return (0); }ponta_de_prova (32060, 13);
} 

