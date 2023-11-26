#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void funcTime(int (*fp)(char *), char *x, char *funcName);

typedef struct StringHashNode {
  struct StringHashNode *next;
  char s[26];
  int max;
} SHN;

///////////// START
int lengthOfLongestSubstring(char *s) {

  if (s[0] == '\0')
    return 0;

  int maxVal = 1;
  int lastColInd = -1;

  int cols[128];
  memset(cols, -1, 128 * sizeof(int));

  int i;
  for (i = 0; s[i] != '\0'; i++) {
    int cmpVal;
    if (cols[s[i]] > lastColInd) {
      cmpVal = cols[s[i]];
      lastColInd = cols[s[i]];
    } else {
      cmpVal = lastColInd;
    }

    if (maxVal < i - cmpVal)
      maxVal = i - cmpVal;

    cols[s[i]] = i;
  }
  return maxVal;
}

//////////// END

int main() {
  char strings[100][100] = {
      "asdf", " ", "bbbbb", "pwwkew",
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
