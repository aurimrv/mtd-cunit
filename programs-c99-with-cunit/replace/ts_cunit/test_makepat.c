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

static void run_makepat_test(void)
{
    cunit_csv_load("test_cases_makepat.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *arg_cell = cunit_csv_cell_by_name(active_row, "arg");
        const char *start_cell = cunit_csv_cell_by_name(active_row, "start");
        const char *delim_cell = cunit_csv_cell_by_name(active_row, "delim");
        int start = atoi(start_cell);
        char delim = delim_cell[0];
        char argbuf[256];
        strcpy(argbuf, arg_cell);
        char pat[100];
        int result = makepat(argbuf, start, delim, pat);
        /*
         * Oracle must observe pat[] as well as the return index: many u-SSDL
         * mutants delete statements that only change the encoded pattern
         * (e.g. stclose) while leaving the same return value.
         */
        char out[512];
        int pos = 0;
        int pi;
        pos += snprintf(out + pos, sizeof(out) - (size_t)pos, "%d#", result);
        for (pi = 0; pi < 100; pi++) {
            pos += snprintf(out + pos, sizeof(out) - (size_t)pos, "%02x",
                            (unsigned char)pat[pi]);
            if (pat[pi] == ENDSTR) {
                break;
            }
            if (pos >= (int)sizeof(out) - 4) {
                break;
            }
        }
        cunit_oracle_check_output(out);
    }
    /* LLM_BODY_END */
}

void register_makepat(void)
{
    CU_add_test(cunit_suite, "makepat", run_makepat_test);
}
