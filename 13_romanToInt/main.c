#include "uthash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_TEST 1

void funcTime(int (*fp)(char *), char *x, int maxCnt, char *funcName);

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

///////////// START

int romanToInt(char *s) {
  int num = 0;
  int x = 12;
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    while (s[i] != roman_nums[x].letter[0])
      x--;

    if (x % 2 == 1) {
      if (len - 1 > i && s[i + 1] == roman_nums[x].letter[1]) {
        num += roman_nums[x].value;
        x -= roman_nums[x].advance;
        i++;
      } else {
        x--;
        i--;
      }
      continue;
    }
    num += roman_nums[x].value;
  }
  return num;
}

//////////// END

int main() {
  int expected[] = {3,    58,   1994, 1,    3999, 3499, 3498, 3333, 2999, 2998,
                    2997, 2499, 2111, 1111, 3000, 2000, 1000, 500,  499};

  char *testcase[] = {"III",       "LVIII",      "MCMXCIV",     "I",
                      "MMMCMXCIX", "MMMCDXCIX",  "MMMCDXCVIII", "MMMCCCXXXIII",
                      "MMCMXCIX",  "MMCMXCVIII", "MMCMXCVII",   "MMCDXCIX",
                      "MMCXI",     "MCXI",       "MMM",         "MM",
                      "M",         "D",          "CDXCIX"};

  for (int i = 0; i < sizeof(testcase) / sizeof(testcase[0]); i++) {
    if (romanToInt(testcase[i]) != expected[i]) {
      printf("Test case %s failed\n", testcase[i]);
      printf("Got %d, expected %d\n", romanToInt(testcase[i]), expected[i]);
      return -1;
    } else {
      printf("Test case %s passed\n", testcase[i]);
      printf("Got %d, expected %d\n", romanToInt(testcase[i]), expected[i]);
    }
  }

  if (TIME_TEST)
    funcTime(romanToInt, "MMMCMXCIX", 10000, "romanToInt");
}

void funcTime(int (*fp)(char *), char *x, int maxCnt, char *funcName) {
  fflush(stdout);
  int retval;

  clock_t start = clock();
  for (int i = 0; i < maxCnt; i++)
    retval = fp(x);
  clock_t end = clock();

  printf("Time to run function %s %d times with val %s is: %f us\n", funcName,
         maxCnt, x, 1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Return value is %d\n", retval);
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
