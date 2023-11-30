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

typedef struct RomanNum {
  char letter[3];
  int length;
  int advance;
  int value;
} RomanNum;

RomanNum roman_nums[13] = {
    {"I", 1, 1, 1},   {"IV", 2, 2, 4},   {"V", 1, 1, 5},   {"IX", 2, 4, 9},
    {"X", 1, 1, 10},  {"XL", 2, 2, 40},  {"L", 1, 1, 50},  {"XC", 2, 4, 90},
    {"C", 1, 1, 100}, {"CD", 2, 2, 400}, {"D", 1, 1, 500}, {"CM", 2, 4, 900},
    {"M", 1, 1, 1000}

};

char *intToRoman(int num) {
  int x = 12;
  int i = 0;

  char *roman = malloc(16);

  while (x >= 0) {
    if (num >= roman_nums[x].value) {
      num -= roman_nums[x].value;
      for (int j = 0; j < roman_nums[x].length; j++)
        roman[i++] = roman_nums[x].letter[j];
    } else {
      if (x % 2 && i > 1 && roman[i - 2] == roman_nums[x].letter[0])
        x -= roman_nums[x].advance;
      else
        x--;
    }
  }

  roman[i] = '\0';

  return roman;
}

//////////// END

int main() {
  int A[] = {3,    58,   1994, 1,    3999, 3499, 3498, 3333, 2999, 2998,
             2997, 2499, 2111, 1111, 3000, 2000, 1000, 500,  499};

  char *expected[] = {"III",       "LVIII",      "MCMXCIV",     "I",
                      "MMMCMXCIX", "MMMCDXCIX",  "MMMCDXCVIII", "MMMCCCXXXIII",
                      "MMCMXCIX",  "MMCMXCVIII", "MMCMXCVII",   "MMCDXCIX",
                      "MMCXI",     "MCXI",       "MMM",         "MM",
                      "M",         "D",          "CDXCIX"};

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
