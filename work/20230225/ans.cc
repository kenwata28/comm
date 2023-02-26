#include <stdio.h>

#include <iostream>
#include <string>

int main() {
  char* cstr = "this is a //string with //comment";
  std::string str(cstr);

  if (1 <= 0) {
    printf("1 is less than 2\n");
  }

  if (1 < 1)  // )aaaaaaaaaaaaa
    printf("aaa\n");

  if (1 < 2) printf("aaa\n");

  if (str.size() > 3) {
    printf("aaa\n");
  }

  if (str.size() > 2) printf("aaa\n");

  if (str.size() > 2 and str.find(')')) printf("aaa\n");

  printf("if (");

  int ii = 0;
  if (ii > 0) {
    printf("1 is less than 2\n");
  } else if (ii == 0) {
    printf("1 is less than 2\n");
  } else {
    printf("1 is less than 2\n");
  }

  return 0;
}
