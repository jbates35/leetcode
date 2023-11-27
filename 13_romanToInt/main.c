#include "uthash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_TEST 0

void funcTime(int (*fp)(char *), char *x, char *funcName);

///////////// START

int romanToInt(char *s) { return 0; }

//////////// END

int main() {
  int expected[] = {3,    58,   1994, 1,    0,    3999, 3499, 3498, 3333, 2999,
                    2998, 2997, 2499, 2111, 1111, 3000, 2000, 1000, 500,  499};

  char *testcase[] = {"III",       "LVIII",       "MCMXCIV",
                      "I",         "0",           "MMMCMXCIX",
                      "MMMCDXCIX", "MMMCDXCVIII", "MMMCCCXXXIII",
                      "MMCMXCIX",  "MMCMXCVIII",  "MMCMXCVII",
                      "MMCDXCIX",  "MMCXI",       "MCXI",
                      "MMM",       "MM",          "M",
                      "D",         "CDXCIX"};

  for (int i = 0; i < sizeof(testcase) / sizeof(testcase[0]); i++) {
    if (romanToInt(testcase[i]) != expected[i]) {
      printf("Test case %s failed\n", testcase[i]);
      printf("Got %d, expected %d\n", romanToInt(testcase[i]), expected[i]);
    } else {
      printf("Test case %s passed\n", testcase[i]);
      printf("Got %d, expected %d\n", romanToInt(testcase[i]), expected[i]);
    }
  }

  if (TIME_TEST)
    funcTime(romanToInt, "MMMCMXCIX", "romanToInt");
}

void funcTime(int (*fp)(char *), char *x, char *funcName) {
  fflush(stdout);
  clock_t start = clock();
  clock_t end = clock();
  start = clock();
  int retval;

  int maxCnt = 1;
  if (TIME_TEST)
    maxCnt = 10000;

  for (int i = 0; i < maxCnt; i++)
    retval = fp(x);
  end = clock();
  printf("Time to run function %s with val %s is: %f us\n", funcName, x,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Return value is %d\n", retval);
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
