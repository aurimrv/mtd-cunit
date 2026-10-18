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

static void run_dodash_test(void)
{
    cunit_csv_load("test_cases_dodash.csv");
    /* LLM_BODY_BEGIN */
    for (active_row = 0; active_row < cunit_csv_row_count(); active_row++) {
        const char *delim_str = cunit_csv_cell_by_name(active_row, "delim");
        const char *src_str = cunit_csv_cell_by_name(active_row, "src");
        const char *i_str = cunit_csv_cell_by_name(active_row, "i");
        const char *dest_str = cunit_csv_cell_by_name(active_row, "dest");
        const char *j_str = cunit_csv_cell_by_name(active_row, "j");
        const char *maxset_str = cunit_csv_cell_by_name(active_row, "maxset");

        char delim = delim_str[0];
        char src_buf[256];
        strncpy(src_buf, src_str, sizeof(src_buf)-1);
        src_buf[sizeof(src_buf)-1] = '\0';
        int i_val = atoi(i_str);
        char dest_buf[256];
        if (dest_str[0] == '\0') {
            dest_buf[0] = '\0';
        } else {
            strncpy(dest_buf, dest_str, sizeof(dest_buf)-1);
            dest_buf[sizeof(dest_buf)-1] = '\0';
        }
        int j_val = atoi(j_str);
        int maxset = atoi(maxset_str);

        dodash(delim, src_buf, &i_val, dest_buf, &j_val, maxset);

        if (j_val < (int)sizeof(dest_buf)) {
            dest_buf[j_val] = '\0';
        } else {
            dest_buf[sizeof(dest_buf)-1] = '\0';
        }

        char output[512];
        snprintf(output, sizeof(output), "dest=%s,j=%d,i=%d", dest_buf, j_val, i_val);
        cunit_oracle_check_output(output);
    }
    /* LLM_BODY_END */
}

void register_dodash(void)
{
    CU_add_test(cunit_suite, "dodash", run_dodash_test);
}
