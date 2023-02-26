#include <stdio.h>

#include <iostream>
#include <string>

int main() {
  char* cstr = "this is a //string with //comment";
  std::string str(cstr);

  if (1 <= 0) {
    printf("1 is less than 2\n");
  }

  if (2 < 1)  // aaaaaaaaaaaaa
    printf("aaa\n");

  if (3 < 2) printf("aaa\n");
  if (4 < 2) printf("aaa\n"); if (5 < 2) printf("aaa\n");

if (6 < 2) printf("aaa\n");

// if (3 < 2) printf("aaa\n");

  if (double(int(str.size())) > 3) {
    printf("aaa\n");
  }

  if (str.size() > 2) printf("aaa\n");

  if (str.size() > 2 and str.find(')')) printf("aaa\n");

  printf(" if (");

  int ii = 0;
  if (ii > 0) {
    printf("ii is larger than 2\n");
  } else if (ii == 0) {
    printf("ii equal to 0\n");
  } else {
    printf("ii is otherwise\n");
  }

  if (1) {
    ii *= 2;
  } else
    if (1)
    printf("aaa");

    return 0;
}
