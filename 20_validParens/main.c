#include "uthash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_TEST 0

void funcTime(bool (*fp)(char *), char *s, char *funcName);

///////////// START

bool isValid(char *s) { return true; }

//////////// END

int main() {

  char *inputs[] = {
      "()",
      "()[]{}",
      "(]",
      "([)]",
      "{[]}",
      "(([]){})",
      "(((())))(((((((((()))))))))))",
      "(({})([])((([]{}{(((((({})(({})([])((([]{}{(((((({}(({})([])((([]{}{(((("
      "(({})(({})([])((([]{}{(((((({}))))))})))))))))}))))))))))})))))))))}))))"
      "(({})([])((([]{}{(((((({}(({})([])((([]{}{(((((({}(({})([])((([]{}{((((("
      "({}())))))})))))))))}))))))))))})))))))",
      "(({})([])((([]{}{(((((({}(({})([])((([]{}{(((((({}(({})([])((([]{}{(((("
      "("};
  bool expected[] = {true, true, false, false, true, true, true, true, false};

  for (int i = 0; i < 6; i++) {
    bool result = isValid(inputs[i]);
    printf("Result for %s is %s\n", inputs[i], result ? "true" : "false");
    printf("Expected for %s is %s\n", inputs[i],
           expected[i] ? "true" : "false");
    printf("Result == Expected: %s\n",
           result == expected[i] ? "true" : "false");

    if (result != expected[i]) {
      exit(1);
    }

    funcTime(isValid, inputs[i], "isValid");
    printf("\n");
  }
}

void funcTime(bool (*fp)(char *), char *s, char *funcName) {
  bool retval;
  clock_t start = clock();
  for (int i = 0; i < 10000; i++)
    retval = fp(s);
  clock_t end = clock();

  fflush(stdout);
  printf("Time to run function %s is: %f us\n", funcName,
         1000000 * (double)(end - start) / CLOCKS_PER_SEC);
  fflush(stdout);
}

// max score is around 1600-1800us for first iteration
