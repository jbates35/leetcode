#include "uthash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_TEST 0

void funcTime(char *(*fp)(int), int x, char *funcName);

///////////// START

char *intToRoman(int num) {
  char *roman = malloc(16);
  return roman;
}

//////////// END

int main() {
  int A[] = {3,    58,   1994, 1,    0,    3999, 3499, 3498, 3333, 2999,
             2998, 2997, 2499, 2111, 1111, 3000, 2000, 1000, 500,  499};

  char *expected[] = {"III",       "LVIII",       "MCMXCIV",
                      "I",         "0",           "MMMCMXCIX",
                      "MMMCDXCIX", "MMMCDXCVIII", "MMMCCCXXXIII",
                      "MMCMXCIX",  "MMCMXCVIII",  "MMCMXCVII",
                      "MMCDXCIX",  "MMCXI",       "MCXI",
                      "MMM",       "MM",          "M",
                      "D",         "CDXCIX"};

  for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++) {
    char *ret = intToRoman(A[i]);
    if (strcmp(ret, expected[i]) != 0) {
      printf("Test failed for %d\n", A[i]);
      printf("Expected %s, got %s\n", expected[i], ret);
      return 1;
    }
    printf("Test passed for %d\n", A[i]);
    printf("Expected %s, got %s\n", expected[i], ret);
  }

  if (TIME_TEST)
    funcTime(intToRoman, 3999, "intToRoman");
}

void funcTime(char *(*fp)(int), int x, char *funcName) {
  fflush(stdout);
  clock_t start = clock();
  clock_t end = clock();
  start = clock();
  char *retval;

  int maxCnt = 1;
  if (TIME_TEST)
    maxCnt = 10000;

  for (int i = 0; i < maxCnt; i++)
    retval = fp(x);
  end = clock();
  printf("Time to run function %s with val %d is: %f us\n", funcName, x,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Return value is %s\n", retval);
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
