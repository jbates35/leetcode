#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funcTime(bool (*fp)(int), int x, char *funcName);

///////////// START

bool isPalindrome(int x) {
  if (x < 0)
    return false;
  if (x < 10)
    return true;

  // First find digits
  unsigned long k = 1;
  while (x >= k)
    k *= 10;
  k /= 10;
  //
  for (int r = 1; r < k; r *= 10) {
    if ((x / k) % 10 != (x / r) % 10)
      return false;

    k /= 10;
  }
  return true;
}

int main() {
  int nums[] = {-121, 121, 10, 1954664591, 195424591, 1954234591};
  for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
    funcTime(isPalindrome, nums[i], "isPalindrome");
    printf("\n\n");
  }
}

void funcTime(bool (*fp)(int), int x, char *funcName) {
  fflush(stdout);
  clock_t start = clock();
  clock_t end = clock();
  start = clock();
  bool result;
  for (int i = 0; i < 10000; i++)
    result = fp(x);
  end = clock();
  printf("Time to run function %s with val %d is: %f us\n", funcName, x,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Result %d is %s", x, result ? "true" : "false");
  fflush(stdout);
}
