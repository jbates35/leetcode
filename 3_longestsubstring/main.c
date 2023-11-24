#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funcTime(int (*fp)(char *), char *x, char *funcName);

typedef struct StringHashNode {
  struct StringHashNode *next;
  char s[26];
  int max;
} SHN;

///////////// START
int lengthOfLongestSubstring(char *s) {

  int maxVal = 0;
  for (int x = 0; s[x] != '\0'; x++) {
    unsigned long matchLower = 0;
    unsigned long matchUpper = 0;
    int i;
    for (i = x; s[i] != '\0'; i++) {
      if (s[i] < 64) {
        if ((1UL << s[i]) & matchLower)
          break;
        matchLower |= (long)(1UL << s[i]);
      } else {
        if ((1UL << (s[i] - 64)) & matchUpper)
          break;
        matchUpper |= (long)(1UL << (s[i] - 64));
      }
    }
    if (i - x > maxVal)
      maxVal = i - x;

    if (s[i] == '\0')
      break;
  }
  return maxVal;
}

//////////// END

int main() {
  char strings[100][100] = {
      "asdasdf", "abcabcbb", "bbbbb", "pwwkew",
      "asjdfoaiwefjowaifaweoifawoeifawefioewffjasdflkjasdflsdafawleij"};
  for (int i = 0; i < 5; i++) {
    funcTime(lengthOfLongestSubstring, strings[i], "lengthOfLongestSubstring");
  }
}

void funcTime(int (*fp)(char *), char *x, char *funcName) {
  fflush(stdout);
  clock_t start = clock();
  clock_t end = clock();
  start = clock();
  int retval;
  for (int i = 0; i < 10000; i++)
    retval = fp(x);
  end = clock();
  printf("Time to run function %s with val %s is: %f us\n", funcName, x,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Return value is %d\n", retval);
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
