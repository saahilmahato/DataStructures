#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

/* Test statistics */
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

/* Color codes for terminal output */
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"

/* Assert macros */
#define assert_equal(expected, actual, fmt) \
    do { \
        tests_run++; \
        if ((expected) == (actual)) { \
            tests_passed++; \
            printf(COLOR_GREEN "✓" COLOR_RESET " PASS: %s:%d - Expected " fmt ", got " fmt "\n", \
                   __FILE__, __LINE__, expected, actual); \
        } else { \
            tests_failed++; \
            printf(COLOR_RED "✗" COLOR_RESET " FAIL: %s:%d - Expected " fmt ", but got " fmt "\n", \
                   __FILE__, __LINE__, expected, actual); \
        } \
    } while (0)

#define assert_equal_int(expected, actual) \
    assert_equal(expected, actual, "%d")

#define assert_equal_size_t(expected, actual) \
    assert_equal(expected, actual, "%zu")

#define assert_equal_ptr(expected, actual) \
    assert_equal(expected, actual, "%p")

#define assert_not_null(ptr) \
    do { \
        tests_run++; \
        if ((ptr) != NULL) { \
            tests_passed++; \
            printf(COLOR_GREEN "✓" COLOR_RESET " PASS: %s:%d - Pointer is not NULL\n", \
                   __FILE__, __LINE__); \
        } else { \
            tests_failed++; \
            printf(COLOR_RED "✗" COLOR_RESET " FAIL: %s:%d - Expected non-NULL pointer\n", \
                   __FILE__, __LINE__); \
        } \
    } while (0)

#define assert_null(ptr) \
    do { \
        tests_run++; \
        if ((ptr) == NULL) { \
            tests_passed++; \
            printf(COLOR_GREEN "✓" COLOR_RESET " PASS: %s:%d - Pointer is NULL\n", \
                   __FILE__, __LINE__); \
        } else { \
            tests_failed++; \
            printf(COLOR_RED "✗" COLOR_RESET " FAIL: %s:%d - Expected NULL pointer, got %p\n", \
                   __FILE__, __LINE__, (void*)(ptr)); \
        } \
    } while (0)

#define assert_true(condition) \
    do { \
        tests_run++; \
        if (condition) { \
            tests_passed++; \
            printf(COLOR_GREEN "✓" COLOR_RESET " PASS: %s:%d - Condition is true\n", \
                   __FILE__, __LINE__); \
        } else { \
            tests_failed++; \
            printf(COLOR_RED "✗" COLOR_RESET " FAIL: %s:%d - Expected true condition\n", \
                   __FILE__, __LINE__); \
        } \
    } while (0)

#define assert_false(condition) \
    do { \
        tests_run++; \
        if (!(condition)) { \
            tests_passed++; \
            printf(COLOR_GREEN "✓" COLOR_RESET " PASS: %s:%d - Condition is false\n", \
                   __FILE__, __LINE__); \
        } else { \
            tests_failed++; \
            printf(COLOR_RED "✗" COLOR_RESET " FAIL: %s:%d - Expected false condition\n", \
                   __FILE__, __LINE__); \
        } \
    } while (0)

/* Test summary functions */
static inline void test_reset(void) {
    tests_run = 0;
    tests_passed = 0;
    tests_failed = 0;
}

static inline void test_summary(void) {
    printf("\n========================================\n");
    printf("Test Summary:\n");
    printf("  Total:  %d\n", tests_run);
    printf(COLOR_GREEN "  Passed: %d\n" COLOR_RESET, tests_passed);
    if (tests_failed > 0) {
        printf(COLOR_RED "  Failed: %d\n" COLOR_RESET, tests_failed);
    } else {
        printf("  Failed: %d\n", tests_failed);
    }
    printf("========================================\n");

    if (tests_failed == 0 && tests_run > 0) {
        printf(COLOR_GREEN "All tests passed!\n" COLOR_RESET);
    }
}

#endif
