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
struct Parens {
  char match;
  bool is_open;
};

struct Parens make_paren(char match, bool is_open) {
  struct Parens retStruct;
  retStruct.match = match;
  retStruct.is_open = is_open;
  return retStruct;
}

struct Parens parens[128];

struct stack {
  int size;
  int top;
  char *s;
};

bool isValid(char *s) {
  parens['('] = make_paren(')', true);
  parens[')'] = make_paren('(', false);
  parens['['] = make_paren(']', true);
  parens[']'] = make_paren('[', false);
  parens['{'] = make_paren('}', true);
  parens['}'] = make_paren('{', false);

  bool retVal = true;

  int arrsize = strlen(s);
  char *s_stack = malloc(arrsize);
  int s_cnt = -1;

  for (int i = 0; s[i] != '\0'; i++) {
    if (parens[s[i]].is_open == true) {
      s_stack[++s_cnt] = s[i];
      continue;
    }

    if (s_cnt != -1 && s_stack[s_cnt] == parens[s[i]].match) {
      s_cnt--;
      continue;
    }

    retVal = false;
    break;
  }

  free(s_stack);
  return retVal && (s_cnt == -1);
}

int main() {

  char *inputs[] = {"()",
                    "({{{{}}}))",
                    "()[]{}",
                    "(]",
                    "([)]",
                    "{[]}",
                    "(([]){})",
                    "(((())))(((((((((())))))))))",
                    "(({})([])((([]{}{(((((({})(({})([])((([]{}{(((((({}(({})"
                    "([])((([]{}{(((("
                    "(({})(({})([])((([]{}{(((((({}))))))})))))))))})))))))))"
                    ")})))))))))}))))"
                    "(({})([])((([]{}{(((((({}(({})([])((([]{}{(((((({}(({})("
                    "[])((([]{}{((((("
                    "({}())))))})))))))))}))))))))))}))))))",
                    "(({})([])((([]{}{(((((({}(({})([])((([]{}{(((((({}(({})("
                    "[])((([]{}{(((("
                    "("};
  bool expected[] = {true, false, true, false, false,
                     true, true,  true, true,  false};

  for (int i = 0; i < sizeof(expected) / sizeof(bool); i++) {
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
