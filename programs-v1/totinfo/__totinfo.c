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


typedef float float_t;
typedef double double_t;
extern int __fpclassify (double __value)
     ;
extern int __signbit (double __value)
     ;
extern int __isinf (double __value)
  ;
extern int __finite (double __value)
  ;
extern int __isnan (double __value)
  ;
extern int __iseqsig (double __x, double __y) ;
extern int __issignaling (double __value)
     ;
 extern double acos (double __x) ; extern double __acos (double __x) ;
 extern double asin (double __x) ; extern double __asin (double __x) ;
 extern double atan (double __x) ; extern double __atan (double __x) ;
 extern double atan2 (double __y, double __x) ; extern double __atan2 (double __y, double __x) ;
 extern double cos (double __x) ; extern double __cos (double __x) ;
 extern double sin (double __x) ; extern double __sin (double __x) ;
 extern double tan (double __x) ; extern double __tan (double __x) ;
 extern double cosh (double __x) ; extern double __cosh (double __x) ;
 extern double sinh (double __x) ; extern double __sinh (double __x) ;
 extern double tanh (double __x) ; extern double __tanh (double __x) ;
 extern double acosh (double __x) ; extern double __acosh (double __x) ;
 extern double asinh (double __x) ; extern double __asinh (double __x) ;
 extern double atanh (double __x) ; extern double __atanh (double __x) ;
 extern double exp (double __x) ; extern double __exp (double __x) ;
extern double frexp (double __x, int *__exponent) ; extern double __frexp (double __x, int *__exponent) ;
extern double ldexp (double __x, int __exponent) ; extern double __ldexp (double __x, int __exponent) ;
 extern double log (double __x) ; extern double __log (double __x) ;
 extern double log10 (double __x) ; extern double __log10 (double __x) ;
extern double modf (double __x, double *__iptr) ; extern double __modf (double __x, double *__iptr) ;
 extern double expm1 (double __x) ; extern double __expm1 (double __x) ;
 extern double log1p (double __x) ; extern double __log1p (double __x) ;
extern double logb (double __x) ; extern double __logb (double __x) ;
 extern double exp2 (double __x) ; extern double __exp2 (double __x) ;
 extern double log2 (double __x) ; extern double __log2 (double __x) ;
 extern double pow (double __x, double __y) ; extern double __pow (double __x, double __y) ;
extern double sqrt (double __x) ; extern double __sqrt (double __x) ;
 extern double hypot (double __x, double __y) ; extern double __hypot (double __x, double __y) ;
 extern double cbrt (double __x) ; extern double __cbrt (double __x) ;
extern double ceil (double __x) ; extern double __ceil (double __x) ;
extern double fabs (double __x) ; extern double __fabs (double __x) ;
extern double floor (double __x) ; extern double __floor (double __x) ;
extern double fmod (double __x, double __y) ; extern double __fmod (double __x, double __y) ;
extern int isinf (double __value)
  ;
extern int finite (double __value)
  ;
extern double drem (double __x, double __y) ; extern double __drem (double __x, double __y) ;
extern double significand (double __x) ; extern double __significand (double __x) ;
extern double copysign (double __x, double __y) ; extern double __copysign (double __x, double __y) ;
extern double nan (const char *__tagb) ; extern double __nan (const char *__tagb) ;
extern int isnan (double __value)
  ;
extern double j0 (double) ; extern double __j0 (double) ;
extern double j1 (double) ; extern double __j1 (double) ;
extern double jn (int, double) ; extern double __jn (int, double) ;
extern double y0 (double) ; extern double __y0 (double) ;
extern double y1 (double) ; extern double __y1 (double) ;
extern double yn (int, double) ; extern double __yn (int, double) ;
 extern double erf (double) ; extern double __erf (double) ;
 extern double erfc (double) ; extern double __erfc (double) ;
extern double lgamma (double) ; extern double __lgamma (double) ;
extern double tgamma (double) ; extern double __tgamma (double) ;
extern double gamma (double) ; extern double __gamma (double) ;
extern double lgamma_r (double, int *__signgamp) ; extern double __lgamma_r (double, int *__signgamp) ;
extern double rint (double __x) ; extern double __rint (double __x) ;
extern double nextafter (double __x, double __y) ; extern double __nextafter (double __x, double __y) ;
extern double nexttoward (double __x, long double __y) ; extern double __nexttoward (double __x, long double __y) ;
extern double remainder (double __x, double __y) ; extern double __remainder (double __x, double __y) ;
extern double scalbn (double __x, int __n) ; extern double __scalbn (double __x, int __n) ;
extern int ilogb (double __x) ; extern int __ilogb (double __x) ;
extern double scalbln (double __x, long int __n) ; extern double __scalbln (double __x, long int __n) ;
extern double nearbyint (double __x) ; extern double __nearbyint (double __x) ;
extern double round (double __x) ; extern double __round (double __x) ;
extern double trunc (double __x) ; extern double __trunc (double __x) ;
extern double remquo (double __x, double __y, int *__quo) ; extern double __remquo (double __x, double __y, int *__quo) ;
extern long int lrint (double __x) ; extern long int __lrint (double __x) ;

extern long long int llrint (double __x) ; extern long long int __llrint (double __x) ;
extern long int lround (double __x) ; extern long int __lround (double __x) ;

extern long long int llround (double __x) ; extern long long int __llround (double __x) ;
extern double fdim (double __x, double __y) ; extern double __fdim (double __x, double __y) ;
extern double fmax (double __x, double __y) ; extern double __fmax (double __x, double __y) ;
extern double fmin (double __x, double __y) ; extern double __fmin (double __x, double __y) ;
extern double fma (double __x, double __y, double __z) ; extern double __fma (double __x, double __y, double __z) ;
extern double scalb (double __x, double __n) ; extern double __scalb (double __x, double __n) ;
extern int __fpclassifyf (float __value)
     ;
extern int __signbitf (float __value)
     ;
extern int __isinff (float __value)
  ;
extern int __finitef (float __value)
  ;
extern int __isnanf (float __value)
  ;
extern int __iseqsigf (float __x, float __y) ;
extern int __issignalingf (float __value)
     ;
 extern float acosf (float __x) ; extern float __acosf (float __x) ;
 extern float asinf (float __x) ; extern float __asinf (float __x) ;
 extern float atanf (float __x) ; extern float __atanf (float __x) ;
 extern float atan2f (float __y, float __x) ; extern float __atan2f (float __y, float __x) ;
 extern float cosf (float __x) ; extern float __cosf (float __x) ;
 extern float sinf (float __x) ; extern float __sinf (float __x) ;
 extern float tanf (float __x) ; extern float __tanf (float __x) ;
 extern float coshf (float __x) ; extern float __coshf (float __x) ;
 extern float sinhf (float __x) ; extern float __sinhf (float __x) ;
 extern float tanhf (float __x) ; extern float __tanhf (float __x) ;
 extern float acoshf (float __x) ; extern float __acoshf (float __x) ;
 extern float asinhf (float __x) ; extern float __asinhf (float __x) ;
 extern float atanhf (float __x) ; extern float __atanhf (float __x) ;
 extern float expf (float __x) ; extern float __expf (float __x) ;
extern float frexpf (float __x, int *__exponent) ; extern float __frexpf (float __x, int *__exponent) ;
extern float ldexpf (float __x, int __exponent) ; extern float __ldexpf (float __x, int __exponent) ;
 extern float logf (float __x) ; extern float __logf (float __x) ;
 extern float log10f (float __x) ; extern float __log10f (float __x) ;
extern float modff (float __x, float *__iptr) ; extern float __modff (float __x, float *__iptr) ;
 extern float expm1f (float __x) ; extern float __expm1f (float __x) ;
 extern float log1pf (float __x) ; extern float __log1pf (float __x) ;
extern float logbf (float __x) ; extern float __logbf (float __x) ;
 extern float exp2f (float __x) ; extern float __exp2f (float __x) ;
 extern float log2f (float __x) ; extern float __log2f (float __x) ;
 extern float powf (float __x, float __y) ; extern float __powf (float __x, float __y) ;
extern float sqrtf (float __x) ; extern float __sqrtf (float __x) ;
 extern float hypotf (float __x, float __y) ; extern float __hypotf (float __x, float __y) ;
 extern float cbrtf (float __x) ; extern float __cbrtf (float __x) ;
extern float ceilf (float __x) ; extern float __ceilf (float __x) ;
extern float fabsf (float __x) ; extern float __fabsf (float __x) ;
extern float floorf (float __x) ; extern float __floorf (float __x) ;
extern float fmodf (float __x, float __y) ; extern float __fmodf (float __x, float __y) ;
extern int isinff (float __value)
  ;
extern int finitef (float __value)
  ;
extern float dremf (float __x, float __y) ; extern float __dremf (float __x, float __y) ;
extern float significandf (float __x) ; extern float __significandf (float __x) ;
extern float copysignf (float __x, float __y) ; extern float __copysignf (float __x, float __y) ;
extern float nanf (const char *__tagb) ; extern float __nanf (const char *__tagb) ;
extern int isnanf (float __value)
  ;
extern float j0f (float) ; extern float __j0f (float) ;
extern float j1f (float) ; extern float __j1f (float) ;
extern float jnf (int, float) ; extern float __jnf (int, float) ;
extern float y0f (float) ; extern float __y0f (float) ;
extern float y1f (float) ; extern float __y1f (float) ;
extern float ynf (int, float) ; extern float __ynf (int, float) ;
 extern float erff (float) ; extern float __erff (float) ;
 extern float erfcf (float) ; extern float __erfcf (float) ;
extern float lgammaf (float) ; extern float __lgammaf (float) ;
extern float tgammaf (float) ; extern float __tgammaf (float) ;
extern float gammaf (float) ; extern float __gammaf (float) ;
extern float lgammaf_r (float, int *__signgamp) ; extern float __lgammaf_r (float, int *__signgamp) ;
extern float rintf (float __x) ; extern float __rintf (float __x) ;
extern float nextafterf (float __x, float __y) ; extern float __nextafterf (float __x, float __y) ;
extern float nexttowardf (float __x, long double __y) ; extern float __nexttowardf (float __x, long double __y) ;
extern float remainderf (float __x, float __y) ; extern float __remainderf (float __x, float __y) ;
extern float scalbnf (float __x, int __n) ; extern float __scalbnf (float __x, int __n) ;
extern int ilogbf (float __x) ; extern int __ilogbf (float __x) ;
extern float scalblnf (float __x, long int __n) ; extern float __scalblnf (float __x, long int __n) ;
extern float nearbyintf (float __x) ; extern float __nearbyintf (float __x) ;
extern float roundf (float __x) ; extern float __roundf (float __x) ;
extern float truncf (float __x) ; extern float __truncf (float __x) ;
extern float remquof (float __x, float __y, int *__quo) ; extern float __remquof (float __x, float __y, int *__quo) ;
extern long int lrintf (float __x) ; extern long int __lrintf (float __x) ;

extern long long int llrintf (float __x) ; extern long long int __llrintf (float __x) ;
extern long int lroundf (float __x) ; extern long int __lroundf (float __x) ;

extern long long int llroundf (float __x) ; extern long long int __llroundf (float __x) ;
extern float fdimf (float __x, float __y) ; extern float __fdimf (float __x, float __y) ;
extern float fmaxf (float __x, float __y) ; extern float __fmaxf (float __x, float __y) ;
extern float fminf (float __x, float __y) ; extern float __fminf (float __x, float __y) ;
extern float fmaf (float __x, float __y, float __z) ; extern float __fmaf (float __x, float __y, float __z) ;
extern float scalbf (float __x, float __n) ; extern float __scalbf (float __x, float __n) ;
extern int __fpclassifyl (long double __value)
     ;
extern int __signbitl (long double __value)
     ;
extern int __isinfl (long double __value)
  ;
extern int __finitel (long double __value)
  ;
extern int __isnanl (long double __value)
  ;
extern int __iseqsigl (long double __x, long double __y) ;
extern int __issignalingl (long double __value)
     ;
 extern long double acosl (long double __x) ; extern long double __acosl (long double __x) ;
 extern long double asinl (long double __x) ; extern long double __asinl (long double __x) ;
 extern long double atanl (long double __x) ; extern long double __atanl (long double __x) ;
 extern long double atan2l (long double __y, long double __x) ; extern long double __atan2l (long double __y, long double __x) ;
 extern long double cosl (long double __x) ; extern long double __cosl (long double __x) ;
 extern long double sinl (long double __x) ; extern long double __sinl (long double __x) ;
 extern long double tanl (long double __x) ; extern long double __tanl (long double __x) ;
 extern long double coshl (long double __x) ; extern long double __coshl (long double __x) ;
 extern long double sinhl (long double __x) ; extern long double __sinhl (long double __x) ;
 extern long double tanhl (long double __x) ; extern long double __tanhl (long double __x) ;
 extern long double acoshl (long double __x) ; extern long double __acoshl (long double __x) ;
 extern long double asinhl (long double __x) ; extern long double __asinhl (long double __x) ;
 extern long double atanhl (long double __x) ; extern long double __atanhl (long double __x) ;
 extern long double expl (long double __x) ; extern long double __expl (long double __x) ;
extern long double frexpl (long double __x, int *__exponent) ; extern long double __frexpl (long double __x, int *__exponent) ;
extern long double ldexpl (long double __x, int __exponent) ; extern long double __ldexpl (long double __x, int __exponent) ;
 extern long double logl (long double __x) ; extern long double __logl (long double __x) ;
 extern long double log10l (long double __x) ; extern long double __log10l (long double __x) ;
extern long double modfl (long double __x, long double *__iptr) ; extern long double __modfl (long double __x, long double *__iptr) ;
 extern long double expm1l (long double __x) ; extern long double __expm1l (long double __x) ;
 extern long double log1pl (long double __x) ; extern long double __log1pl (long double __x) ;
extern long double logbl (long double __x) ; extern long double __logbl (long double __x) ;
 extern long double exp2l (long double __x) ; extern long double __exp2l (long double __x) ;
 extern long double log2l (long double __x) ; extern long double __log2l (long double __x) ;
 extern long double powl (long double __x, long double __y) ; extern long double __powl (long double __x, long double __y) ;
extern long double sqrtl (long double __x) ; extern long double __sqrtl (long double __x) ;
 extern long double hypotl (long double __x, long double __y) ; extern long double __hypotl (long double __x, long double __y) ;
 extern long double cbrtl (long double __x) ; extern long double __cbrtl (long double __x) ;
extern long double ceill (long double __x) ; extern long double __ceill (long double __x) ;
extern long double fabsl (long double __x) ; extern long double __fabsl (long double __x) ;
extern long double floorl (long double __x) ; extern long double __floorl (long double __x) ;
extern long double fmodl (long double __x, long double __y) ; extern long double __fmodl (long double __x, long double __y) ;
extern int isinfl (long double __value)
  ;
extern int finitel (long double __value)
  ;
extern long double dreml (long double __x, long double __y) ; extern long double __dreml (long double __x, long double __y) ;
extern long double significandl (long double __x) ; extern long double __significandl (long double __x) ;
extern long double copysignl (long double __x, long double __y) ; extern long double __copysignl (long double __x, long double __y) ;
extern long double nanl (const char *__tagb) ; extern long double __nanl (const char *__tagb) ;
extern int isnanl (long double __value)
  ;
extern long double j0l (long double) ; extern long double __j0l (long double) ;
extern long double j1l (long double) ; extern long double __j1l (long double) ;
extern long double jnl (int, long double) ; extern long double __jnl (int, long double) ;
extern long double y0l (long double) ; extern long double __y0l (long double) ;
extern long double y1l (long double) ; extern long double __y1l (long double) ;
extern long double ynl (int, long double) ; extern long double __ynl (int, long double) ;
 extern long double erfl (long double) ; extern long double __erfl (long double) ;
 extern long double erfcl (long double) ; extern long double __erfcl (long double) ;
extern long double lgammal (long double) ; extern long double __lgammal (long double) ;
extern long double tgammal (long double) ; extern long double __tgammal (long double) ;
extern long double gammal (long double) ; extern long double __gammal (long double) ;
extern long double lgammal_r (long double, int *__signgamp) ; extern long double __lgammal_r (long double, int *__signgamp) ;
extern long double rintl (long double __x) ; extern long double __rintl (long double __x) ;
extern long double nextafterl (long double __x, long double __y) ; extern long double __nextafterl (long double __x, long double __y) ;
extern long double nexttowardl (long double __x, long double __y) ; extern long double __nexttowardl (long double __x, long double __y) ;
extern long double remainderl (long double __x, long double __y) ; extern long double __remainderl (long double __x, long double __y) ;
extern long double scalbnl (long double __x, int __n) ; extern long double __scalbnl (long double __x, int __n) ;
extern int ilogbl (long double __x) ; extern int __ilogbl (long double __x) ;
extern long double scalblnl (long double __x, long int __n) ; extern long double __scalblnl (long double __x, long int __n) ;
extern long double nearbyintl (long double __x) ; extern long double __nearbyintl (long double __x) ;
extern long double roundl (long double __x) ; extern long double __roundl (long double __x) ;
extern long double truncl (long double __x) ; extern long double __truncl (long double __x) ;
extern long double remquol (long double __x, long double __y, int *__quo) ; extern long double __remquol (long double __x, long double __y, int *__quo) ;
extern long int lrintl (long double __x) ; extern long int __lrintl (long double __x) ;

extern long long int llrintl (long double __x) ; extern long long int __llrintl (long double __x) ;
extern long int lroundl (long double __x) ; extern long int __lroundl (long double __x) ;

extern long long int llroundl (long double __x) ; extern long long int __llroundl (long double __x) ;
extern long double fdiml (long double __x, long double __y) ; extern long double __fdiml (long double __x, long double __y) ;
extern long double fmaxl (long double __x, long double __y) ; extern long double __fmaxl (long double __x, long double __y) ;
extern long double fminl (long double __x, long double __y) ; extern long double __fminl (long double __x, long double __y) ;
extern long double fmal (long double __x, long double __y, long double __z) ; extern long double __fmal (long double __x, long double __y, long double __z) ;
extern long double scalbl (long double __x, long double __n) ; extern long double __scalbl (long double __x, long double __n) ;
extern int __fpclassifyf128 (double __value)
     ;
extern int __signbitf128 (double __value)
     ;
extern int __isinff128 (double __value)
  ;
extern int __finitef128 (double __value)
  ;
extern int __isnanf128 (double __value)
  ;
extern int __iseqsigf128 (double __x, double __y) ;
extern int __issignalingf128 (double __value)
     ;
extern int signgam;
enum
  {
    FP_NAN =
      0,
    FP_INFINITE =
      1,
    FP_ZERO =
      2,
    FP_SUBNORMAL =
      3,
    FP_NORMAL =
      4
  };

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

typedef int bool;
typedef void *pointer;
extern double ChiSqTbl( int r, int c, const long *f, int *pdf );
extern double InfoTbl( int r, int c, const long *f, int *pdf );
extern double Gamma( double z ), LGamma( double z ),
  Factorial( int n ), LFactorial( int n ),
  BCoeff( int n, int k ),
  Beta( double z, double w ),
  PGamma( double a, double x ), QGamma( double a, double x ),
  Erf( double x ), Erfc( double x ),
  CPoisson( double x, int k ),
  PChiSq( double chisq, int nu ), QChiSq( double chisq, int nu );
static char line[256];
long f[1000];
int r;
int c;
FILE *mystdin;
int dispatch(void)
{
 char *p;
 int i;
 int j;
 double info;
 int infodf;
 double totinfo = 0.0;
 int totdf;
 totdf = 0;
 while (fgets(line, 256, mystdin) != ((void *)0)) {
  for (p = line; *p != '\0' && ((*__ctype_b_loc ())[(int) (((int)*p))] & (unsigned short int) _ISspace); ++p) ;
  if (*p == '\0')
   continue;
  if (*p == '#') {
   (void)fputs(line, stdout);
   continue;
  }
  if (sscanf(p, "%d %d\n", &r, &c) != 2) {
   (void)fputs("* invalid row/column line *\n", stdout);
   return 1;
  }
  if (r * c > 1000) {
   (void)fputs("* table too large *\n", stdout);
   return 1;
  }
  for (i = 0; i < r; ++i)
   for (j = 0; j < c; ++j)
    if (fscanf(mystdin, " %ld", &f[(i)*c+(j)]) != 1) {
     (void)fputs("* EOF in table *\n",
          stdout);
     return 1;
    }
  info = InfoTbl(r, c, f, &infodf);
  if (info >= 0.0) {
   (void)printf("2info = %5.2f\tdf = %2d\tq = %7.4f\n",
         info, infodf, QChiSq(info, infodf)
       );
   totinfo += info;
   totdf += infodf;
  } else
   (void)fputs(info < -3.5 ? "out of memory\n"
        : info < -2.5 ? "table too small\n"
        : info < -1.5 ? "negative freq\n"
        : "table all zeros\n", stdout);
 }
 if (totdf <= 0) {
  (void)fputs("\n*** no information accumulated ***\n", stdout);
  return 1;
 }
 (void)printf("\ntotal 2info = %5.2f\tdf = %2d\tq = %7.4f\n",
       totinfo, totdf, QChiSq(totinfo, totdf)
     );
 return 0;
}
double LGamma(double x)
{
 static const double cof[6] = {
  76.18009173, -86.50532033, 24.01409822,
  -1.231739516, 0.120858003e-2, -0.536382e-5
 };
 double tmp, ser;
 int j;
 if (--x < 0.0) {
  double pix = 3.14159265358979323846264338327950288419716939937511 * x;
  return log(pix / sin(pix)) - LGamma(1.0 - x);
 }
 tmp = x + 5.5;
 tmp -= (x + 0.5) * log(tmp);
 ser = 1.0;
 for (j = 0; j < 6; ++j)
  ser += cof[j] / ++x;
 return -tmp + log(2.50662827465 * ser);
}
double gser(double a, double x)
{
 double ap, del, sum;
 int n;
 if (x <= 0.0)
  return 0.0;
 del = sum = 1.0 / (ap = a);
 for (n = 1; n <= 100; ++n) {
  sum += del *= x / ++ap;
  if (((del) < 0 ? -(del) : (del)) < ((sum) < 0 ? -(sum) : (sum)) * 3.0e-7)
   return sum * exp(-x + a * log(x) - LGamma(a));
 }
 return sum * exp(-x + a * log(x) - LGamma(a));
}
double gcf(double a, double x)
{
 int n;
 double gold = 0.0, fac = 1.0, b1 = 1.0, b0 = 0.0, a0 = 1.0, a1 = x;
 double g = 0.0;
 for (n = 1; n <= 100; ++n) {
  double anf;
  double an = (double)n;
  double ana = an - a;
  a0 = (a1 + a0 * ana) * fac;
  b0 = (b1 + b0 * ana) * fac;
  anf = an * fac;
  b1 = x * b0 + anf * b1;
  a1 = x * a0 + anf * a1;
  if (a1 != 0.0) {
   g = b1 * (fac = 1.0 / a1);
   gold = g - gold;
   if (((gold) < 0 ? -(gold) : (gold)) < 3.0e-7 * ((g) < 0 ? -(g) : (g)))
    return exp(-x + a * log(x) - LGamma(a)) * g;
   gold = g;
  }
 }
 return exp(-x + a * log(x) - LGamma(a)) * g;
}
double QGamma(double a, double x)
{
 return x < a + 1.0 ? 1.0 - gser(a, x) : gcf(a, x);
}
double QChiSq(double chisq, int df)
{
 return QGamma((double)df / 2.0, chisq / 2.0);
}
double InfoTbl(int r, int c, const long *f, int *pdf)
{
 int i;
 int j;
 double N;
 double info = 0;
 double *xi;
 double *xj;
 int rdf = r - 1;
 int cdf = c - 1;
 if (rdf <= 0 || cdf <= 0) {
  info = -3.0;
  goto ret3;
 }
 *pdf = rdf * cdf;
 if ((xi = (double *)malloc(r * sizeof(double))) == ((void *)0)) {
  info = -4.0;
  goto ret3;
 }
 if ((xj = (double *)malloc(c * sizeof(double))) == ((void *)0)) {
  info = -4.0;
  goto ret2;
 }
 N = 0.0;
 for (i = 0; i < r; ++i) {
  double sum = 0.0;
  for (j = 0; j < c; ++j) {
   long k = f[(i)*c+(j)];
   if (k < 0L) {
    info = -2.0;
    goto ret1;
   }
   sum += (double)k;
  }
  N += xi[i] = sum;
 }
 if (N <= 0.0) {
  info = -1.0;
  goto ret1;
 }
 for (j = 0; j < c; ++j) {
  double sum = 0.0;
  for (i = 0; i < r; ++i)
   sum += (double)f[(i)*c+(j)];
  xj[j] = sum;
 }
 info = N * log(N);
 for (i = 0; i < r; ++i) {
  double pi = xi[i];
  if (pi > 0.0)
   info -= pi * log(pi);
  for (j = 0; j < c; ++j) {
   double pij = (double)f[(i)*c+(j)];
   if (pij > 0.0)
    info += pij * log(pij);
  }
 }
 for (j = 0; j < c; ++j) {
  double pj = xj[j];
  if (pj > 0.0)
   info -= pj * log(pj);
 }
 info *= 2.0;
 ret1:
 free((pointer) xj);
 ret2:
 free((pointer) xi);
 ret3:
 return info;
}
