#include "cunit_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

extern void register_new_ele(void);
extern void register_new_list(void);
extern void register_append_ele(void);
extern void register_find_nth(void);
extern void register_del_ele(void);
extern void register_free_ele(void);
extern void register_finish_process(void);
extern void register_finish_all_processes(void);
extern void register_schedule(void);
extern void register_upgrade_process_prio(void);
extern void register_unblock_process(void);
extern void register_quantum_expire(void);
extern void register_block_process(void);
extern void register_new_process(void);
extern void register_add_process(void);
extern void register_init_prio_queue(void);
extern void register_initialize(void);
extern void register_dispatch(void);

CU_pSuite cunit_suite = NULL;
int cunit_results_emitted = 0;
int cunit_real_stdout_fd = -1;

void cunit_mark_results_emitted(void)
{
    cunit_results_emitted = 1;
}

static const char *cunit_names[] = { "new_ele", "new_list", "append_ele", "find_nth", "del_ele", "free_ele", "finish_process", "finish_all_processes", "schedule", "upgrade_process_prio", "unblock_process", "quantum_expire", "block_process", "new_process", "add_process", "init_prio_queue", "initialize", "dispatch", NULL };

static void cunit_usage(const char *argv0)
{
    fprintf(stderr,
        "Usage: %s --data <dir> <function_name> <test_number> | --data <dir> --list | --data <dir> --all <testset.txt file>\n",
        argv0);
}

static int cunit_known(const char *name)
{
    int index;
    for (index = 0; cunit_names[index] != NULL; index++) {
        if (strcmp(cunit_names[index], name) == 0) {
            return 1;
        }
    }
    return 0;
}

static void cunit_register_name(const char *name)
{
    if (strcmp(name, "new_ele") == 0) { register_new_ele(); return; }
    if (strcmp(name, "new_list") == 0) { register_new_list(); return; }
    if (strcmp(name, "append_ele") == 0) { register_append_ele(); return; }
    if (strcmp(name, "find_nth") == 0) { register_find_nth(); return; }
    if (strcmp(name, "del_ele") == 0) { register_del_ele(); return; }
    if (strcmp(name, "free_ele") == 0) { register_free_ele(); return; }
    if (strcmp(name, "finish_process") == 0) { register_finish_process(); return; }
    if (strcmp(name, "finish_all_processes") == 0) { register_finish_all_processes(); return; }
    if (strcmp(name, "schedule") == 0) { register_schedule(); return; }
    if (strcmp(name, "upgrade_process_prio") == 0) { register_upgrade_process_prio(); return; }
    if (strcmp(name, "unblock_process") == 0) { register_unblock_process(); return; }
    if (strcmp(name, "quantum_expire") == 0) { register_quantum_expire(); return; }
    if (strcmp(name, "block_process") == 0) { register_block_process(); return; }
    if (strcmp(name, "new_process") == 0) { register_new_process(); return; }
    if (strcmp(name, "add_process") == 0) { register_add_process(); return; }
    if (strcmp(name, "init_prio_queue") == 0) { register_init_prio_queue(); return; }
    if (strcmp(name, "initialize") == 0) { register_initialize(); return; }
    if (strcmp(name, "dispatch") == 0) { register_dispatch(); return; }
}

static int cunit_blank_line(const char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r') {
        text++;
    }
    return *text == '\0';
}

static void cunit_strip_line(char *text)
{
    size_t length = strlen(text);
    while (length > 0 && (text[length - 1] == '\n' || text[length - 1] == '\r')) {
        text[--length] = '\0';
    }
}

static int cunit_read_selection(const char *path)
{
    FILE *file = fopen(path, "r");
    char line[1024];
    char function[128];
    char number[512];
    char extra[8];
    if (file == NULL) {
        return 1;
    }
    while (fgets(line, sizeof line, file) != NULL) {
        cunit_strip_line(line);
        if (cunit_blank_line(line)) {
            fclose(file);
            return 1;
        }
        if (sscanf(line, "%127s %511s %7s", function, number, extra) != 2) {
            fclose(file);
            return 1;
        }
        if (!cunit_known(function) || !cunit_case_has_number(function, number)) {
            fclose(file);
            return 1;
        }
        if (cunit_add_pair(function, number) != 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

static int cunit_list_cases(void)
{
    int index;
    int row;
    char basename[256];
    for (index = 0; cunit_names[index] != NULL; index++) {
        snprintf(basename, sizeof basename, "test_cases_%s.csv", cunit_names[index]);
        cunit_csv_load(basename);
        for (row = 0; row < cunit_csv_row_count(); row++) {
            printf("%s %s\n", cunit_names[index], cunit_csv_cell_by_name(row, "test_number"));
        }
    }
    return 0;
}

static int cunit_run_selected(void)
{
    int index;
    cunit_real_stdout_fd = dup(fileno(stdout));
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return 1;
    }
    cunit_suite = CU_add_suite("generated", NULL, NULL);
    if (cunit_suite == NULL) {
        CU_cleanup_registry();
        return 1;
    }
    for (index = 0; cunit_names[index] != NULL; index++) {
        if (cunit_function_selected(cunit_names[index])) {
            cunit_register_name(cunit_names[index]);
        }
    }
    CU_basic_set_mode(CU_BRM_NORMAL);
    /* Hide CUnit's nondeterministic elapsed-time line; fall back if capture fails. */
    {
        int saved_stdout = -1;
        FILE *captured = NULL;
        int filter_ready = 0;
        char line[4096];

        fflush(stdout);
        saved_stdout = dup(fileno(stdout));
        captured = tmpfile();
        if (saved_stdout >= 0 && captured != NULL
            && dup2(fileno(captured), fileno(stdout)) >= 0) {
            filter_ready = 1;
        } else {
            if (saved_stdout >= 0) {
                close(saved_stdout);
                saved_stdout = -1;
            }
            if (captured != NULL) {
                fclose(captured);
                captured = NULL;
            }
        }
        CU_basic_run_tests();
        if (filter_ready) {
            fflush(stdout);
            dup2(saved_stdout, fileno(stdout));
            close(saved_stdout);
            rewind(captured);
            while (fgets(line, sizeof line, captured) != NULL) {
                if (strstr(line, "Elapsed time") != NULL) {
                    continue;
                }
                fputs(line, stdout);
            }
            fclose(captured);
        }
    }
    {
        unsigned int failed = CU_get_number_of_failures();
        unsigned int passed = CU_get_number_of_successes();
        unsigned int total = CU_get_number_of_tests_run();
        printf("Results: %u passed, %u failed out of %u total tests\n", passed, failed, total);
        cunit_mark_results_emitted();
        CU_cleanup_registry();
        return failed == 0 ? 0 : 1;
    }
}

static int cunit_line_is_elapsed(const char *line)
{
    return strstr(line, "Elapsed time") != NULL;
}

static int cunit_parse_results(const char *line, unsigned *passed, unsigned *failed, unsigned *total)
{
    return sscanf(line, "Results: %u passed, %u failed out of %u total tests",
        passed, failed, total) == 3;
}

static void cunit_note_child_death(unsigned *passed, unsigned *failed, unsigned *total)
{
    /* Exit status 0 is not a pass when the child printed no Results: line. */
    *passed = 0;
    *failed = 1;
    *total = 1;
}

static int cunit_consume_child_stdout(FILE *stream, unsigned *passed, unsigned *failed, unsigned *total)
{
    char line[4096];
    int saw_results = 0;
    unsigned child_passed = 0;
    unsigned child_failed = 0;
    unsigned child_total = 0;

    while (fgets(line, sizeof line, stream) != NULL) {
        unsigned parsed_passed;
        unsigned parsed_failed;
        unsigned parsed_total;
        if (cunit_line_is_elapsed(line)) {
            continue;
        }
        if (cunit_parse_results(line, &parsed_passed, &parsed_failed, &parsed_total)) {
            if (!saw_results) {
                child_passed = parsed_passed;
                child_failed = parsed_failed;
                child_total = parsed_total;
                saw_results = 1;
            }
            continue;
        }
        fputs(line, stdout);
    }
    if (!saw_results) {
        cunit_note_child_death(passed, failed, total);
        return 0;
    }
    *passed = child_passed;
    *failed = child_failed;
    *total = child_total;
    return 1;
}

static void cunit_spawn_one_case(
    const char *argv0,
    const char *data_dir,
    const char *function,
    const char *number,
    unsigned *passed,
    unsigned *failed,
    unsigned *total)
{
    int pipe_fds[2];
    posix_spawn_file_actions_t actions;
    pid_t pid;
    FILE *captured;
    char *child_argv[6];
    int spawned;

    fflush(stdout);
    fflush(stderr);
    if (pipe(pipe_fds) != 0) {
        cunit_note_child_death(passed, failed, total);
        return;
    }
    if (posix_spawn_file_actions_init(&actions) != 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        cunit_note_child_death(passed, failed, total);
        return;
    }
    posix_spawn_file_actions_addclose(&actions, pipe_fds[0]);
    posix_spawn_file_actions_adddup2(&actions, pipe_fds[1], STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&actions, pipe_fds[1]);
    child_argv[0] = (char *)argv0;
    child_argv[1] = "--data";
    child_argv[2] = (char *)data_dir;
    child_argv[3] = (char *)function;
    child_argv[4] = (char *)number;
    child_argv[5] = NULL;
    spawned = posix_spawn(&pid, argv0, &actions, NULL, child_argv, environ);
    posix_spawn_file_actions_destroy(&actions);
    close(pipe_fds[1]);
    if (spawned != 0) {
        close(pipe_fds[0]);
        cunit_note_child_death(passed, failed, total);
        return;
    }
    captured = fdopen(pipe_fds[0], "r");
    if (captured == NULL) {
        close(pipe_fds[0]);
        waitpid(pid, NULL, 0);
        cunit_note_child_death(passed, failed, total);
        return;
    }
    cunit_consume_child_stdout(captured, passed, failed, total);
    fclose(captured);
    /* Reap the child. Its exit code is not a pass or a fail; Results: is. */
    waitpid(pid, NULL, 0);
}

static int cunit_run_all_isolated(const char *argv0, const char *data_dir)
{
    unsigned passed = 0;
    unsigned failed = 0;
    unsigned total = 0;
    int index;

    for (index = 0; index < cunit_pair_count; index++) {
        unsigned child_passed = 0;
        unsigned child_failed = 0;
        unsigned child_total = 0;
        cunit_spawn_one_case(
            argv0,
            data_dir,
            cunit_pair_fn[index],
            cunit_pair_num[index],
            &child_passed,
            &child_failed,
            &child_total);
        passed += child_passed;
        failed += child_failed;
        total += child_total;
    }
    printf("Results: %u passed, %u failed out of %u total tests\n", passed, failed, total);
    fflush(stdout);
    return failed == 0 ? 0 : 1;
}

int main(int argc, char **argv)
{
    if (argc < 4 || strcmp(argv[1], "--data") != 0 || argv[2][0] == '\0') {
        cunit_usage(argv[0]);
        return 1;
    }
    if (setenv("CUNIT_DATA_DIR", argv[2], 1) != 0) {
        return 1;
    }
    if (argc == 4 && strcmp(argv[3], "--list") == 0) {
        return cunit_list_cases();
    }
    if (argc == 5 && strcmp(argv[3], "--all") == 0) {
        if (cunit_read_selection(argv[4]) != 0) {
            return 1;
        }
        /* One process per line. Children flush gcov on normal exit; the parent only aggregates. */
        return cunit_run_all_isolated(argv[0], argv[2]);
    }
    if (argc == 5 && strcmp(argv[3], "--list") != 0 && strcmp(argv[3], "--all") != 0) {
        if (!cunit_known(argv[3]) || !cunit_case_has_number(argv[3], argv[4])) {
            return 1;
        }
        if (cunit_add_pair(argv[3], argv[4]) != 0) {
            return 1;
        }
        if (setenv("CUNIT_SELECT_MODE", "one", 1) != 0
            || setenv("CUNIT_SELECT_FUNCTION", argv[3], 1) != 0
            || setenv("CUNIT_SELECT_NUMBER", argv[4], 1) != 0) {
            return 1;
        }
        return cunit_run_selected();
    }
    cunit_usage(argv[0]);
    return 1;
}
