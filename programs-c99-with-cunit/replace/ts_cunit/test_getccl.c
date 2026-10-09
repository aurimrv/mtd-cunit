#include "cunit_common.h"
#include "cunit_gcov.h"
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# define false 0
# define true  1
# define MAXSTR 100
# define MAXPAT MAXSTR
# define ENDSTR  '\0'
# define ESCAPE  '@'
# define CLOSURE '*'
# define BOL     '%'
# define EOL     '$'
# define ANY     '?'
# define CCL     '['
# define CCLEND  ']'
# define NEGATE  '^'
# define NCCL    '!'
# define LITCHAR 'c'
# define DITTO   -1
# define DASH    '-'
# define TAB     9
# define NEWLINE 10
# define CLOSIZE 1
typedef char	bool;
typedef char	character;
typedef char string[MAXSTR];
#include "replace.h"
/* Source-local typedefs and constants (verified at seed time). */
#define NUL 0
/* Project function prototypes (verified at seed time). */
extern bool get_line(char *s, int maxsize);
extern int addstr(char c, char *outset, int *j, int maxset);
extern char esc(char *s, int *i);
extern void dodash(char delim, char *src, int *i, char *dest, int *j, int maxset);
extern bool getccl(char *arg, int *i, char *pat, int *j);
extern void stclose(char *pat, int *j, int lastj);
extern bool in_set_2(char c);
extern bool in_pat_set(char c);
extern int makepat(char *arg, int start, char delim, char *pat);
extern int getpat(char *arg, char *pat);
extern int makesub(char *arg, int from, character delim, char *sub);
extern bool getsub(char *arg, char *sub);
extern bool locate(character c, char *pat, int offset);
extern bool omatch(char *lin, int *i, char *pat, int j);
extern int patsize(char *pat, int n);
extern int amatch(char *lin, int offset, char *pat, int j);
extern void putsub(char *lin, int s1, int s2, char *sub);
extern void subline(char *lin, char *pat, char *sub);
extern void change(char *pat, char *sub);
extern void Caseerror(int n);

static void run_getccl_test(void)
{
    cunit_csv_load("test_cases_getccl.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *arg_s = cunit_csv_cell_by_name(active_row, "arg");
        const char *i_s = cunit_csv_cell_by_name(active_row, "i");
        const char *pat_s = cunit_csv_cell_by_name(active_row, "pat");
        const char *j_s = cunit_csv_cell_by_name(active_row, "j");
        char arg_buf[256];
        char pat_buf[256];
        int i_val = 0;
        int j_val = 0;
        if (arg_s) { strncpy(arg_buf, arg_s, sizeof(arg_buf)-1); arg_buf[sizeof(arg_buf)-1] = '\0'; } else arg_buf[0] = '\0';
        if (pat_s) { strncpy(pat_buf, pat_s, sizeof(pat_buf)-1); pat_buf[sizeof(pat_buf)-1] = '\0'; } else pat_buf[0] = '\0';
        if (i_s) i_val = atoi(i_s);
        if (j_s) j_val = atoi(j_s);
        bool ret = getccl(arg_buf, &i_val, pat_buf, &j_val);
        char out[32];
        snprintf(out, sizeof(out), "%d", ret ? 1 : 0);
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_getccl(void)
{
    CU_add_test(cunit_suite, "getccl", run_getccl_test);
}
