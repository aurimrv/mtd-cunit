#ifndef CMAGUT_CUNIT_COMMON_H
#define CMAGUT_CUNIT_COMMON_H

#include <CUnit/Basic.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern CU_pSuite cunit_suite;

#define CUNIT_CSV_MAX_ROWS 64
#define CUNIT_CSV_MAX_COLS 32

static char *cunit_csv_headers[CUNIT_CSV_MAX_COLS];
static char *cunit_csv_cells[CUNIT_CSV_MAX_ROWS][CUNIT_CSV_MAX_COLS];
static int cunit_csv_ncols = 0;
static int cunit_csv_nrows = 0;
static int active_row = 0;

#define CUNIT_MAX_PAIRS 256
static int cunit_filter_on = 0;
static char cunit_pair_fn[CUNIT_MAX_PAIRS][128];
static char cunit_pair_num[CUNIT_MAX_PAIRS][512];
static int cunit_pair_count = 0;

static char *cunit_capture_buf = NULL;
static size_t cunit_capture_cap = 0;
static char cunit_capture_path[256];
static int cunit_saved_stdout = -1;
static char cunit_function_name[128];
extern int cunit_results_emitted;
extern int cunit_real_stdout_fd;
static int cunit_expect_exit_armed = 0;

static void cunit_set_function_name(const char *basename);
static void cunit_decode_stdout_escapes(const char *src, char *dst, size_t dst_size);
static void cunit_capture_stdout_end(void);
static void cunit_emit_obs(const char *column, const char *value);
static const char *cunit_csv_cell_by_name(int row, const char *column);
static int cunit_capture_mode(void);

static void cunit_free_str(char **slot)
{
    if (slot != NULL && *slot != NULL) {
        free(*slot);
        *slot = NULL;
    }
}

static int cunit_set_str(char **slot, const char *src, size_t length)
{
    char *fresh;
    if (src == NULL) {
        src = "";
        length = 0;
    }
    fresh = (char *)malloc(length + 1);
    if (fresh == NULL) {
        fprintf(stderr, "cmagut harness: out of memory while storing a CSV cell\n");
        return -1;
    }
    memcpy(fresh, src, length);
    fresh[length] = '\0';
    free(*slot);
    *slot = fresh;
    return 0;
}

static void cunit_csv_clear(void)
{
    int row;
    int col;
    for (col = 0; col < CUNIT_CSV_MAX_COLS; col++) {
        cunit_free_str(&cunit_csv_headers[col]);
    }
    for (row = 0; row < CUNIT_CSV_MAX_ROWS; row++) {
        for (col = 0; col < CUNIT_CSV_MAX_COLS; col++) {
            cunit_free_str(&cunit_csv_cells[row][col]);
        }
    }
    cunit_csv_ncols = 0;
    cunit_csv_nrows = 0;
}

static int cunit_dyn_append(char **buf, size_t *length, size_t *capacity, char ch)
{
    if (*length + 1 >= *capacity) {
        size_t next = *capacity == 0 ? 64 : (*capacity * 2);
        char *fresh = (char *)realloc(*buf, next);
        if (fresh == NULL) {
            fprintf(stderr, "cmagut harness: out of memory while parsing a CSV field\n");
            return -1;
        }
        *buf = fresh;
        *capacity = next;
    }
    (*buf)[(*length)++] = ch;
    (*buf)[*length] = '\0';
    return 0;
}

static int cunit_split_csv(char *line, char **fields, int max_fields)
{
    int count = 0;
    char *cursor = line;
    while (count < max_fields) {
        if (*cursor == '"') {
            char *buf = NULL;
            size_t length = 0;
            size_t capacity = 0;
            cursor++;
            while (*cursor != '\0') {
                if (*cursor == '"') {
                    if (cursor[1] == '"') {
                        if (cunit_dyn_append(&buf, &length, &capacity, '"') != 0) {
                            free(buf);
                            return -1;
                        }
                        cursor += 2;
                        continue;
                    }
                    cursor++;
                    break;
                }
                if (cunit_dyn_append(&buf, &length, &capacity, *cursor) != 0) {
                    free(buf);
                    return -1;
                }
                cursor++;
            }
            if (buf == NULL) {
                buf = (char *)malloc(1);
                if (buf == NULL) {
                    fprintf(stderr, "cmagut harness: out of memory while parsing a CSV field\n");
                    return -1;
                }
                buf[0] = '\0';
            }
            fields[count] = buf;
        } else {
            char *start = cursor;
            size_t length;
            while (*cursor != '\0' && *cursor != ',') {
                cursor++;
            }
            length = (size_t)(cursor - start);
            fields[count] = NULL;
            if (cunit_set_str(&fields[count], start, length) != 0) {
                return -1;
            }
        }
        count++;
        if (*cursor != ',') {
            break;
        }
        cursor++;
    }
    return count;
}

static void cunit_free_fields(char **fields, int count)
{
    int index;
    for (index = 0; index < count; index++) {
        cunit_free_str(&fields[index]);
    }
}

static void cunit_strip_newline(char *text);

static int cunit_add_pair(const char *function, const char *number)
{
    if (cunit_pair_count >= CUNIT_MAX_PAIRS) {
        return -1;
    }
    snprintf(cunit_pair_fn[cunit_pair_count], sizeof cunit_pair_fn[0], "%s", function);
    snprintf(cunit_pair_num[cunit_pair_count], sizeof cunit_pair_num[0], "%s", number);
    cunit_pair_count++;
    cunit_filter_on = 1;
    return 0;
}

static int cunit_function_selected(const char *function)
{
    int index;
    for (index = 0; index < cunit_pair_count; index++) {
        if (strcmp(cunit_pair_fn[index], function) == 0) {
            return 1;
        }
    }
    return 0;
}

static int cunit_selection_keeps(const char *function, const char *number)
{
    const char *mode = getenv("CUNIT_SELECT_MODE");
    const char *path;
    FILE *file;
    char line[1024];
    char selected_function[128];
    char selected_number[512];
    char extra[8];

    if (mode == NULL || mode[0] == '\0') {
        return 1;
    }
    if (strcmp(mode, "one") == 0) {
        const char *selected_fn = getenv("CUNIT_SELECT_FUNCTION");
        const char *selected_num = getenv("CUNIT_SELECT_NUMBER");
        if (selected_fn == NULL || selected_num == NULL) {
            return 0;
        }
        return strcmp(selected_fn, function) == 0 && strcmp(selected_num, number) == 0;
    }
    if (strcmp(mode, "file") != 0) {
        return 0;
    }
    path = getenv("CUNIT_SELECT_FILE");
    if (path == NULL) {
        return 0;
    }
    file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }
    while (fgets(line, sizeof line, file) != NULL) {
        cunit_strip_newline(line);
        if (sscanf(line, "%127s %511s %7s", selected_function, selected_number, extra) != 2) {
            continue;
        }
        if (strcmp(selected_function, function) == 0 && strcmp(selected_number, number) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

static void cunit_strip_newline(char *text)
{
    size_t length = strlen(text);
    while (length > 0 && (text[length - 1] == '\n' || text[length - 1] == '\r')) {
        text[--length] = '\0';
    }
}

static int cunit_has_column(const char *column)
{
    int col;
    for (col = 0; col < cunit_csv_ncols; col++) {
        if (cunit_csv_headers[col] != NULL && strcmp(cunit_csv_headers[col], column) == 0) {
            return 1;
        }
    }
    return 0;
}

static int cunit_case_has_number(const char *function, const char *number)
{
    char path[1024];
    char *line = NULL;
    size_t line_cap = 0;
    ssize_t line_len;
    const char *data_dir;
    FILE *file;
    char *headers[CUNIT_CSV_MAX_COLS];
    char *fields[CUNIT_CSV_MAX_COLS];
    int ncols;
    int number_col = -1;
    int col;
    int found = 0;

    for (col = 0; col < CUNIT_CSV_MAX_COLS; col++) {
        headers[col] = NULL;
        fields[col] = NULL;
    }
    data_dir = getenv("CUNIT_DATA_DIR");
    if (data_dir == NULL || data_dir[0] == '\0') {
        data_dir = "ts_data";
    }
    snprintf(path, sizeof path, "%s/test_cases_%s.csv", data_dir, function);
    file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }
    line_len = getline(&line, &line_cap, file);
    if (line_len < 0) {
        free(line);
        fclose(file);
        return 0;
    }
    cunit_strip_newline(line);
    ncols = cunit_split_csv(line, headers, CUNIT_CSV_MAX_COLS);
    if (ncols < 0) {
        cunit_free_fields(headers, CUNIT_CSV_MAX_COLS);
        free(line);
        fclose(file);
        return 0;
    }
    for (col = 0; col < ncols; col++) {
        if (strcmp(headers[col], "test_number") == 0) {
            number_col = col;
            break;
        }
    }
    if (number_col < 0) {
        cunit_free_fields(headers, ncols);
        free(line);
        fclose(file);
        return 0;
    }
    while ((line_len = getline(&line, &line_cap, file)) >= 0) {
        int count;
        cunit_strip_newline(line);
        if (line[0] == '\0') {
            continue;
        }
        cunit_free_fields(fields, CUNIT_CSV_MAX_COLS);
        count = cunit_split_csv(line, fields, CUNIT_CSV_MAX_COLS);
        if (count < 0) {
            break;
        }
        if (number_col < count && strcmp(fields[number_col], number) == 0) {
            found = 1;
            cunit_free_fields(fields, count);
            break;
        }
        cunit_free_fields(fields, count);
    }
    cunit_free_fields(headers, ncols);
    free(line);
    fclose(file);
    return found;
}

static int cunit_csv_load(const char *basename)
{
    char path[1024];
    const char *data_dir;
    FILE *file;
    char *line = NULL;
    size_t line_cap = 0;
    ssize_t line_len;
    const char *slash = strrchr(basename, '/');
    const char *name = slash == NULL ? basename : slash + 1;
    char *fields[CUNIT_CSV_MAX_COLS];
    int col;

    for (col = 0; col < CUNIT_CSV_MAX_COLS; col++) {
        fields[col] = NULL;
    }
    cunit_set_function_name(name);
    cunit_csv_clear();
    data_dir = getenv("CUNIT_DATA_DIR");
    if (data_dir == NULL || data_dir[0] == '\0') {
        data_dir = "ts_data";
    }
    snprintf(path, sizeof path, "%s/%s", data_dir, name);
    file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }
    line_len = getline(&line, &line_cap, file);
    if (line_len >= 0) {
        int count;
        cunit_strip_newline(line);
        count = cunit_split_csv(line, fields, CUNIT_CSV_MAX_COLS);
        if (count < 0) {
            free(line);
            fclose(file);
            cunit_csv_clear();
            return 0;
        }
        cunit_csv_ncols = count;
        for (col = 0; col < count; col++) {
            cunit_csv_headers[col] = fields[col];
            fields[col] = NULL;
        }
    }
    while (cunit_csv_nrows < CUNIT_CSV_MAX_ROWS && (line_len = getline(&line, &line_cap, file)) >= 0) {
        int count;
        char *decoded = NULL;
        cunit_strip_newline(line);
        if (line[0] == '\0') {
            continue;
        }
        cunit_free_fields(fields, CUNIT_CSV_MAX_COLS);
        count = cunit_split_csv(line, fields, CUNIT_CSV_MAX_COLS);
        if (count < 0) {
            free(line);
            fclose(file);
            cunit_csv_clear();
            return 0;
        }
        for (col = 0; col < cunit_csv_ncols; col++) {
            const char *raw = col < count && fields[col] != NULL ? fields[col] : "";
            size_t raw_len = strlen(raw);
            decoded = (char *)malloc(raw_len + 1);
            if (decoded == NULL) {
                fprintf(stderr, "cmagut harness: out of memory while decoding a CSV cell\n");
                cunit_free_fields(fields, count);
                free(line);
                fclose(file);
                cunit_csv_clear();
                return 0;
            }
            cunit_decode_stdout_escapes(raw, decoded, raw_len + 1);
            if (cunit_set_str(&cunit_csv_cells[cunit_csv_nrows][col], decoded, strlen(decoded)) != 0) {
                free(decoded);
                cunit_free_fields(fields, count);
                free(line);
                fclose(file);
                cunit_csv_clear();
                return 0;
            }
            free(decoded);
        }
        cunit_free_fields(fields, count);
        {
            const char *number = "";
            for (col = 0; col < cunit_csv_ncols; col++) {
                if (cunit_csv_headers[col] != NULL && strcmp(cunit_csv_headers[col], "test_number") == 0) {
                    number = cunit_csv_cells[cunit_csv_nrows][col];
                    break;
                }
            }
            if (!cunit_selection_keeps(cunit_function_name, number == NULL ? "" : number)) {
                for (col = 0; col < cunit_csv_ncols; col++) {
                    cunit_free_str(&cunit_csv_cells[cunit_csv_nrows][col]);
                }
                continue;
            }
        }
        cunit_csv_nrows++;
    }
    free(line);
    fclose(file);
    return cunit_csv_nrows;
}

static int cunit_csv_row_count(void)
{
    return cunit_csv_nrows;
}

static const char *cunit_csv_cell_by_name(int row, const char *column)
{
    int col;
    if (row < 0 || row >= cunit_csv_nrows) {
        return "";
    }
    for (col = 0; col < cunit_csv_ncols; col++) {
        if (cunit_csv_headers[col] != NULL && strcmp(cunit_csv_headers[col], column) == 0) {
            return cunit_csv_cells[row][col] == NULL ? "" : cunit_csv_cells[row][col];
        }
    }
    return "";
}

static void cunit_capture_stdout_begin(void)
{
    int fd;
    fflush(stdout);
    snprintf(cunit_capture_path, sizeof cunit_capture_path, "/tmp/cmagut-capture-%d.txt", (int)getpid());
    cunit_saved_stdout = dup(fileno(stdout));
    fd = open(cunit_capture_path, O_CREAT | O_TRUNC | O_RDWR, 0600);
    if (fd >= 0 && cunit_saved_stdout >= 0) {
        dup2(fd, fileno(stdout));
        close(fd);
    }
    if (cunit_capture_buf != NULL) {
        cunit_capture_buf[0] = '\0';
    }
}

static int cunit_capture_grow(size_t need)
{
    size_t next;
    char *fresh;
    if (need <= cunit_capture_cap) {
        return 0;
    }
    next = cunit_capture_cap == 0 ? 8192 : cunit_capture_cap;
    while (next < need) {
        next *= 2;
    }
    fresh = (char *)realloc(cunit_capture_buf, next);
    if (fresh == NULL) {
        fprintf(stderr, "cmagut harness: out of memory while capturing stdout\n");
        return -1;
    }
    cunit_capture_buf = fresh;
    cunit_capture_cap = next;
    return 0;
}

static void cunit_capture_stdout_end(void)
{
    FILE *file;
    size_t nread = 0;
    fflush(stdout);
    if (cunit_saved_stdout >= 0) {
        dup2(cunit_saved_stdout, fileno(stdout));
        close(cunit_saved_stdout);
        cunit_saved_stdout = -1;
    }
    file = fopen(cunit_capture_path, "r");
    if (file == NULL) {
        if (cunit_capture_buf != NULL) {
            cunit_capture_buf[0] = '\0';
        }
        return;
    }
    if (cunit_capture_grow(8192) != 0) {
        fclose(file);
        cunit_free_str(&cunit_capture_buf);
        cunit_capture_cap = 0;
        return;
    }
    for (;;) {
        size_t chunk;
        if (nread + 1 >= cunit_capture_cap) {
            if (cunit_capture_grow(cunit_capture_cap * 2) != 0) {
                fclose(file);
                cunit_free_str(&cunit_capture_buf);
                cunit_capture_cap = 0;
                return;
            }
        }
        chunk = fread(cunit_capture_buf + nread, 1, cunit_capture_cap - nread - 1, file);
        if (chunk == 0) {
            break;
        }
        nread += chunk;
    }
    if (nread > 0 && cunit_capture_buf[nread - 1] == '\n') {
        nread--;
    }
    cunit_capture_buf[nread] = '\0';
    fclose(file);
}

static const char *cunit_captured_stdout(void)
{
    return cunit_capture_buf == NULL ? "" : cunit_capture_buf;
}

static void cunit_set_function_name(const char *basename)
{
    const char *prefix = "test_cases_";
    size_t prefix_len = strlen(prefix);
    size_t length;
    if (strncmp(basename, prefix, prefix_len) == 0) {
        basename += prefix_len;
    }
    snprintf(cunit_function_name, sizeof cunit_function_name, "%s", basename);
    length = strlen(cunit_function_name);
    if (length >= 4 && strcmp(cunit_function_name + length - 4, ".csv") == 0) {
        cunit_function_name[length - 4] = '\0';
    }
}

static int cunit_capture_mode(void)
{
    const char *flag = getenv("CUNIT_CAPTURE");
    return flag != NULL && strcmp(flag, "1") == 0;
}

static void cunit_json_escape(FILE *out, const char *text)
{
    const unsigned char *cursor = (const unsigned char *)(text == NULL ? "" : text);
    fputc('"', out);
    while (*cursor != '\0') {
        if (*cursor == '"' || *cursor == '\\') {
            fputc('\\', out);
            fputc((int)*cursor, out);
        } else if (*cursor == '\n') {
            fputs("\\n", out);
        } else if (*cursor == '\r') {
            fputs("\\r", out);
        } else if (*cursor == '\t') {
            fputs("\\t", out);
        } else if (*cursor < 0x20 || *cursor >= 0x80) {
            /* Portable JSON: controls and high bytes as \\u00xx (valid UTF-8 on the wire). */
            fprintf(out, "\\u%04x", (unsigned int)*cursor);
        } else {
            fputc((int)*cursor, out);
        }
        cursor++;
    }
    fputc('"', out);
}

static void cunit_emit_obs(const char *column, const char *value)
{
    const char *number = cunit_csv_cell_by_name(active_row, "test_number");
    fputs("CMAGUT_OBS ", stdout);
    fputc('{', stdout);
    fputs("\"function\":", stdout);
    cunit_json_escape(stdout, cunit_function_name);
    fputs(",\"test_number\":", stdout);
    cunit_json_escape(stdout, number);
    fputs(",\"column\":", stdout);
    cunit_json_escape(stdout, column);
    fputs(",\"value\":", stdout);
    cunit_json_escape(stdout, value == NULL ? "" : value);
    fputs("}\n", stdout);
    fflush(stdout);
}

static int cunit_hex_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static void cunit_decode_stdout_escapes(const char *src, char *dst, size_t dst_size)
{
    size_t out = 0;
    if (src == NULL) {
        src = "";
    }
    while (*src != '\0' && out + 1 < dst_size) {
        if (src[0] == '\\' && src[1] != '\0') {
            if (src[1] == 'n') {
                dst[out++] = '\n';
                src += 2;
                continue;
            }
            if (src[1] == 'r') {
                dst[out++] = '\r';
                src += 2;
                continue;
            }
            if (src[1] == 't') {
                dst[out++] = '\t';
                src += 2;
                continue;
            }
            if (src[1] == '\\') {
                dst[out++] = '\\';
                src += 2;
                continue;
            }
            if (src[1] == 'u') {
                int h0 = cunit_hex_value(src[2]);
                int h1 = cunit_hex_value(src[3]);
                int h2 = cunit_hex_value(src[4]);
                int h3 = cunit_hex_value(src[5]);
                if (h0 >= 0 && h1 >= 0 && h2 >= 0 && h3 >= 0) {
                    unsigned int code = (unsigned int)((h0 << 12) | (h1 << 8) | (h2 << 4) | h3);
                    dst[out++] = (char)(code & 0xffu);
                    src += 6;
                    continue;
                }
            }
        }
        dst[out++] = *src++;
    }
    dst[out] = '\0';
}

void cunit_mark_results_emitted(void);

static void cunit_finalize_expect_exit(void)
{
    int failed = 0;
    if (!cunit_expect_exit_armed || cunit_results_emitted) {
        return;
    }
    cunit_results_emitted = 1;
    if (cunit_saved_stdout >= 0) {
        cunit_capture_stdout_end();
        /* Leave CUnit's tmpfile redirect before CMAGUT_OBS, or the observation is lost. */
        if (cunit_real_stdout_fd >= 0) {
            fflush(stdout);
            dup2(cunit_real_stdout_fd, fileno(stdout));
        }
        if (cunit_has_column("expected_stdout")) {
            const char *captured = cunit_capture_buf == NULL ? "" : cunit_capture_buf;
            if (cunit_capture_mode()) {
                cunit_emit_obs("expected_stdout", captured);
            } else if (strcmp(captured, cunit_csv_cell_by_name(active_row, "expected_stdout")) != 0) {
                failed = 1;
            }
        }
    }
    /* CUnit may still be redirecting stdout into a tmpfile when exit runs mid-suite. */
    if (cunit_real_stdout_fd >= 0) {
        fflush(stdout);
        dup2(cunit_real_stdout_fd, fileno(stdout));
    }
    if (failed) {
        printf("Results: 0 passed, 1 failed out of 1 total tests\n");
    } else {
        printf("Results: 1 passed, 0 failed out of 1 total tests\n");
    }
    fflush(stdout);
}

static void cunit_expect_exit(void)
{
    if (!cunit_expect_exit_armed) {
        cunit_expect_exit_armed = 1;
        atexit(cunit_finalize_expect_exit);
    }
}

static void cunit_oracle_check_output(const char *actual)
{
    const char *expected;
    if (cunit_capture_mode()) {
        cunit_emit_obs("expected_output", actual);
        return;
    }
    /* Cells are decoded once at CSV load. */
    expected = cunit_csv_cell_by_name(active_row, "expected_output");
    CU_ASSERT_STRING_EQUAL(actual, expected);
}

static void cunit_oracle_check_stdout(void)
{
    const char *expected;
    const char *captured = cunit_capture_buf == NULL ? "" : cunit_capture_buf;
    if (cunit_capture_mode()) {
        cunit_emit_obs("expected_stdout", captured);
        return;
    }
    /* Cells are decoded once at CSV load. */
    expected = cunit_csv_cell_by_name(active_row, "expected_stdout");
    CU_ASSERT_STRING_EQUAL(captured, expected);
}

static void cunit_assert_stdout_equal(const char *expected, const char *actual)
{
    if (cunit_capture_mode()) {
        cunit_emit_obs("expected_stdout", actual);
        return;
    }
    /* expected from cunit_csv_cell_by_name is already decoded at load. */
    CU_ASSERT_STRING_EQUAL(actual, expected);
}

/*
 * Agnostic post-state fingerprints for void / in-place mutators.
 * Serialize observable buffers into oracle strings (never leave expected empty).
 */
static int cunit_fingerprint_ints(char *out, size_t out_sz, const int *a, int n)
{
    size_t pos = 0;
    int i;
    if (out == NULL || out_sz == 0) {
        return -1;
    }
    out[0] = '\0';
    if (a == NULL || n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        int w;
        if (i > 0) {
            if (pos + 1 >= out_sz) {
                break;
            }
            out[pos++] = ',';
            out[pos] = '\0';
        }
        w = snprintf(out + pos, out_sz - pos, "%d", a[i]);
        if (w < 0) {
            return -1;
        }
        pos += (size_t)w;
        if (pos >= out_sz) {
            out[out_sz - 1] = '\0';
            break;
        }
    }
    return 0;
}

static int cunit_fingerprint_doubles(
    char *out, size_t out_sz, const double *a, int n, const char *fmt
)
{
    size_t pos = 0;
    int i;
    if (fmt == NULL || fmt[0] == '\0') {
        fmt = "%.2f";
    }
    if (out == NULL || out_sz == 0) {
        return -1;
    }
    out[0] = '\0';
    if (a == NULL || n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        int w;
        if (i > 0) {
            if (pos + 1 >= out_sz) {
                break;
            }
            out[pos++] = ',';
            out[pos] = '\0';
        }
        w = snprintf(out + pos, out_sz - pos, fmt, a[i]);
        if (w < 0) {
            return -1;
        }
        pos += (size_t)w;
        if (pos >= out_sz) {
            out[out_sz - 1] = '\0';
            break;
        }
    }
    return 0;
}

static int cunit_fingerprint_cstrs(char *out, size_t out_sz, char *const *a, int n)
{
    size_t pos = 0;
    int i;
    if (out == NULL || out_sz == 0) {
        return -1;
    }
    out[0] = '\0';
    if (a == NULL || n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        const char *s = a[i] == NULL ? "" : a[i];
        size_t sl = strlen(s);
        if (i > 0) {
            if (pos + 1 >= out_sz) {
                break;
            }
            out[pos++] = ',';
            out[pos] = '\0';
        }
        if (pos + sl >= out_sz) {
            sl = out_sz - pos - 1;
        }
        memcpy(out + pos, s, sl);
        pos += sl;
        out[pos] = '\0';
        if (pos + 1 >= out_sz) {
            break;
        }
    }
    return 0;
}

static int cunit_fingerprint_bytes(
    char *out, size_t out_sz, const unsigned char *p, int n
)
{
    size_t pos = 0;
    int i;
    if (out == NULL || out_sz == 0) {
        return -1;
    }
    out[0] = '\0';
    if (p == NULL || n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        int w = snprintf(out + pos, out_sz - pos, "%02x", (unsigned int)p[i]);
        if (w < 0) {
            return -1;
        }
        pos += (size_t)w;
        if (pos >= out_sz) {
            out[out_sz - 1] = '\0';
            break;
        }
    }
    return 0;
}

#endif
