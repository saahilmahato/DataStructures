#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

/* Global counters for test results */
extern int tests_run;
extern int tests_failed;

/* Helper function to report failure */
static inline void test_fail(const char *file, int line, const char *msg) {
    fprintf(stderr, "%s:%d: failure: %s\n", file, line, msg);
    tests_failed++;
}

/* Generic equality assertion that works well for both integers and pointers */
#define ASSERT_EQUAL(expected, actual) \
    do { \
        tests_run++; \
        typeof(expected) __exp = (expected); \
        typeof(actual) __act = (actual); \
        \
        if (__exp != __act) { \
            char msg[256]; \
            \
            /* Detect if the type is a pointer (or integer the same size as a pointer) */ \
            if (sizeof(__exp) == sizeof(void*)) { \
                snprintf(msg, sizeof(msg), \
                         "ASSERT_EQUAL failed: expected %p, got %p (" #expected " vs " #actual ")", \
                         (void*)__exp, (void*)__act); \
            } else { \
                /* Assume integer-like type */ \
                snprintf(msg, sizeof(msg), \
                         "ASSERT_EQUAL failed: expected %lld, got %lld (" #expected " vs " #actual ")", \
                         (long long)__exp, (long long)__act); \
            } \
            \
            test_fail(__FILE__, __LINE__, msg); \
        } \
    } while (0)

/* Other common assertions */
#define ASSERT_NOT_EQUAL(not_expected, actual) \
    do { \
        tests_run++; \
        typeof(not_expected) __nexp = (not_expected); \
        typeof(actual) __act = (actual); \
        \
        if (__nexp == __act) { \
            char msg[256]; \
            if (sizeof(__nexp) == sizeof(void*)) { \
                snprintf(msg, sizeof(msg), \
                         "ASSERT_NOT_EQUAL failed: both are %p (" #not_expected " == " #actual ")", \
                         (void*)__act); \
            } else { \
                snprintf(msg, sizeof(msg), \
                         "ASSERT_NOT_EQUAL failed: both are %lld (" #not_expected " == " #actual ")", \
                         (long long)__act); \
            } \
            test_fail(__FILE__, __LINE__, msg); \
        } \
    } while (0)

#define ASSERT_TRUE(cond) \
    do { \
        tests_run++; \
        if (!(cond)) { \
            test_fail(__FILE__, __LINE__, "ASSERT_TRUE(" #cond ") failed"); \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    do { \
        tests_run++; \
        if ((ptr) != NULL) { \
            test_fail(__FILE__, __LINE__, "ASSERT_NULL(" #ptr ") failed: pointer is not NULL"); \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        tests_run++; \
        if ((ptr) == NULL) { \
            test_fail(__FILE__, __LINE__, "ASSERT_NOT_NULL(" #ptr ") failed: pointer is NULL"); \
        } \
    } while (0)

/* Optional: Print summary and exit with appropriate status */
#define TEST_SUMMARY() \
    do { \
        printf("Tests run: %d, Failed: %d\n", tests_run, tests_failed); \
        exit(tests_failed ? EXIT_FAILURE : EXIT_SUCCESS); \
    } while (0)

#endif