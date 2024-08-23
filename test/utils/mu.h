// mu.h - Minimalist unit testing framework.
// Copyright (C) 2024  Mathias Hörtnagl <mathias.hoertnagl[ÄT]gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <stdio.h>
#include <string.h>

// clang-format off

typedef struct
{
  int tests_run;
  int tests_failed;
} Mu;

/**
 * Defines a standalone unit test program.
 * 
 * @param body The body block containing 
 *             the unit tests. 
 */
#define mu_unit(body)                                                        \
int main()                                                                   \
{                                                                            \
  Mu __mu__ = {                                                              \
    .tests_run    = 0,                                                       \
    .tests_failed = 0                                                        \
  };                                                                         \
  printf("\n═══════════════════════════════════════════════════════════\n"); \
  printf(" µ Unit v1.5\n");                                                  \
  printf("───────────────────────────────────────────────────────────\n");   \
  printf(" Running file %s\n\n", __FILE__);                                  \
  body                                                                       \
  printf("───────────────────────────────────────────────────────────\n");   \
  if (__mu__.tests_failed == 0) {                                            \
    printf(                                                                  \
      " PASSED %d TESTS\n",                                                  \
      __mu__.tests_run                                                       \
    );                                                                       \
  } else {                                                                   \
    printf(                                                                  \
      " FAILED %d of %d TESTS\n",                                            \
      __mu__.tests_failed,                                                   \
      __mu__.tests_run                                                       \
    );                                                                       \
  }                                                                          \
  printf("═══════════════════════════════════════════════════════════\n\n"); \
  return 0;                                                                  \
}

/**
 * Defines a single unit test.
 * 
 * @param name The name of the unit test.
 * @param body The test function body block. 
 */
#define test(name, body)        \
  {                             \
    int fails = 0;              \
    printf(" ▶ %s\n", name);    \
    body                        \
    if (fails == 0) {           \
      printf("   🗹  OK\n\n");  \
    } else {                    \
      printf("   ⬜ FAIL\n\n"); \
    }                           \
    __mu__.tests_run++;         \
  }                

/**
 * Fails and prints the failing message. 
 * 
 * If you wish to exit early, it is required that you
 * return an exit value.
 * @code
 * fail("File not found");
 * return 0;
 * @endcode
 * 
 * @param __format The failing message template.
 * @param args     Optional template arguments.
 */
#define fail(__format, args...)                         \
  {                                                     \
    if (fails == 0) {                                   \
      __mu__.tests_failed++;                            \
    }                                                   \
    printf("    ▸ %d: "__format"\n", __LINE__, ##args); \
    fails++;                                            \
  }

/**
 * Asserts that the test condition is true or prints the 
 * failing message if the condition is not satisfied.
 * 
 * @param test     The test condition.
 * @param __format The failing message template.
 * @param args     Optional template arguments.
 */
#define assert(test, __format, args...) \
  if (!(test)) fail(__format, ##args)

/**
 * Asserts that the actual pointer is equal 
 * to the expected pointer or prints a fixed 
 * message indicating the mismatch. 
 * 
 * @param act The actual pointer.
 * @param exp The expected pointer.
 */
#define assert_pointers_equal(act, exp)   \
  assert(                                 \
    (exp) == (act),                       \
    "Expected pointer [%p] but got [%p]", \
    (void *)(exp),                        \
    (void *)(act)                         \
  )

/**
 * Asserts that the actual unsigned integer is 
 * equal to the expected unsigned integer or 
 * prints a fixed message indicating the 
 * mismatch. 
 * 
 * @param act The actual unsigned integer.
 * @param exp The expected unsigned integer.
 */
#define assert_unsigned_equal(act, exp)      \
  assert(                                    \
    (unsigned long)(exp) == (unsigned long)(act),                          \
    "Expected unsigned [%lu] but got [%lu]", \
    (unsigned long)(exp),                    \
    (unsigned long)(act)                     \
  )

/**
 * Asserts that the actual signed integer is 
 * equal to the expected signed integer or 
 * prints a fixed message indicating the 
 * mismatch. 
 * 
 * @param act The actual signed integer.
 * @param exp The expected signed integer.
 */
#define assert_signed_equal(act, exp)      \
  assert(                                  \
    (signed long)(exp) == (signed long)(act),                        \
    "Expected signed [%ld] but got [%ld]", \
    (signed long)(exp),                    \
    (signed long)(act)                     \
  )

/**
 * Asserts that the actual string is equal 
 * to the expected string or prints a fixed
 * message indicating the mismatch.
 * 
 * @param act The actual string.
 * @param exp The expected string.
 */
#define assert_str_equal(act, exp)       \
  assert(                                \
    !strcmp(exp, act),                   \
    "Expected string [%s] but got [%s]", \
    exp,                                 \
    act                                  \
  )

// clang-format on
