
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

typedef struct _job {
    struct _job *next, *prev;
    int val ;
    short priority;
} Ele, *Ele_Ptr;
typedef struct list
{
  Ele *first;
  Ele *last;
  int mem_count;
} List;
Ele *new_ele(int new_num);
List *new_list(void);
List *append_ele(List *a_list, Ele *a_ele);
Ele *find_nth(List *f_list, int n);
List *del_ele(List *d_list, Ele *d_ele);
void free_ele(Ele *ptr);
void finish_process(void);
void finish_all_processes(void);
void schedule(void);
void upgrade_process_prio(int prio, float ratio);
void unblock_process(float ratio);
void quantum_expire(void);
void block_process(void);
Ele *new_process(int prio);
void add_process(int prio);
void init_prio_queue(int prio, int num_proc);
void initialize(void);
void dispatch(void);
FILE *mystdin;
Ele * new_ele(int new_num)
{
 Ele *ele;
 ele = (Ele *) malloc(sizeof(Ele));
 ele->next = ((void *)0);
 ele->prev = ((void *)0);
 ele->val = new_num;
 return ele;
}
List *new_list(void)
{
 List *list;
 list = (List *) malloc(sizeof(List));
 list->first = ((void *)0);
 list->last = ((void *)0);
 list->mem_count = 0;
 return (list);
}
List *append_ele(List *a_list, Ele *a_ele)
{
 if (!a_list)
  a_list = new_list();
 a_ele->prev = a_list->last;
 if (a_list->last)
  a_list->last->next = a_ele;
 else
  a_list->first = a_ele;
 a_list->last = a_ele;
 a_ele->next = ((void *)0);
 a_list->mem_count++;
 return (a_list);
}
Ele *find_nth(List *f_list, int n)
{
 Ele *f_ele;
 int i;
 if (!f_list)
  return ((void *)0);
 f_ele = f_list->first;
 for (i = 1; f_ele && (i < n); i++)
  f_ele = f_ele->next;
 return f_ele;
}
List *del_ele(List *d_list, Ele *d_ele)
{
 if (!d_list || !d_ele)
  return (((void *)0));
 if (d_ele->next)
  d_ele->next->prev = d_ele->prev;
 else
  d_list->last = d_ele->prev;
 if (d_ele->prev)
  d_ele->prev->next = d_ele->next;
 else
  d_list->first = d_ele->next;
 d_list->mem_count--;
 return (d_list);
}
void free_ele(Ele *ptr)
{
 free(ptr);
}
int alloc_proc_num;
int num_processes;
Ele *cur_proc;
List *prio_queue[3 + 1];
List *block_queue;
void finish_process(void)
{
 schedule();
 if (cur_proc) {
  fprintf(stdout, "%d ", cur_proc->val);
  free_ele(cur_proc);
  num_processes--;
 }
}
void finish_all_processes(void)
{
 int i;
 int total;
 total = num_processes;
 for (i = 0; i < total; i++)
  finish_process();
}
void schedule(void)
{
 int i;
 cur_proc = ((void *)0);
 for (i = 3; i > 0; i--) {
  if (prio_queue[i]->mem_count > 0) {
   cur_proc = prio_queue[i]->first;
   prio_queue[i] = del_ele(prio_queue[i], cur_proc);
   return;
  }
 }
}
void upgrade_process_prio(int prio, float ratio)
{
 int count;
 int n;
 Ele *proc;
 List *src_queue, *dest_queue;
 if (prio >= 3)
  return;
 src_queue = prio_queue[prio];
 dest_queue = prio_queue[prio + 1];
 count = src_queue->mem_count;
 if (count > 0) {
  n = (int)(count * ratio + 1);
  proc = find_nth(src_queue, n);
  if (proc) {
   src_queue = del_ele(src_queue, proc);
   proc->priority = prio;
   dest_queue = append_ele(dest_queue, proc);
  }
 }
}
void unblock_process(float ratio)
{
 int count;
 int n;
 Ele *proc;
 int prio;
 if (block_queue) {
  count = block_queue->mem_count;
  n = (int)(count * ratio + 1);
  proc = find_nth(block_queue, n);
  if (proc) {
   block_queue = del_ele(block_queue, proc);
   prio = proc->priority;
   prio_queue[prio] = append_ele(prio_queue[prio], proc);
  }
 }
}
void quantum_expire(void)
{
 int prio;
 schedule();
 if (cur_proc) {
  prio = cur_proc->priority;
  prio_queue[prio] = append_ele(prio_queue[prio], cur_proc);
 }
}
void block_process(void)
{
 schedule();
 if (cur_proc) {
  block_queue = append_ele(block_queue, cur_proc);
 }
}
Ele * new_process(int prio)
{
 Ele *proc;
 proc = new_ele(alloc_proc_num++);
 proc->priority = prio;
 num_processes++;
 return proc;
}
void add_process(int prio)
{
 Ele *proc;
 proc = new_process(prio);
 prio_queue[prio] = append_ele(prio_queue[prio], proc);
}
void init_prio_queue(int prio, int num_proc)
{
 List *queue;
 Ele *proc;
 int i;
 queue = new_list();
 for (i = 0; i < num_proc; i++) {
  proc = new_process(prio);
  queue = append_ele(queue, proc);
 }
 prio_queue[prio] = queue;
}
void initialize(void)
{
 alloc_proc_num = 0;
 num_processes = 0;
}
void dispatch(void)
{
 int command;
 int prio;
 float ratio;
 int status;
 for (status = fscanf(mystdin, "%d", &command);
      ((status != (-1)) && status);
      status = fscanf(mystdin, "%d", &command)) {
  switch (command) {
  case 6:
   finish_process();
   break;
  case 3:
   block_process();
   break;
  case 5:
   quantum_expire();
   break;
  case 4:
   fscanf(mystdin, "%f", &ratio);
   unblock_process(ratio);
   break;
  case 2:
   fscanf(mystdin, "%d", &prio);
   fscanf(mystdin, "%f", &ratio);
   if (prio > 3 || prio <= 0) {
    fprintf(stdout, "** invalid priority\n");
    return;
   } else
    upgrade_process_prio(prio, ratio);
   break;
  case 1:
   fscanf(mystdin, "%d", &prio);
   if (prio > 3 || prio <= 0) {
    fprintf(stdout, "** invalid priority\n");
    return;
   } else
    add_process(prio);
   break;
  case 7:
   finish_all_processes();
   break;
  }
 }
}
