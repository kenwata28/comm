#include <stdio.h>

#include <iostream>

int main() {
  char* str = "this is a //string with //comment";

  printf("%s\n", str);

  printf("%s/*", str);  // comment out

  // \n comment out

  // " double quauted aaaaa /* "

  std::cout << " aaa \
  //bbb /*\
  ccc \
  " << std::endl;

  if ('a' or '\"') {
    printf("aaa");
  }

  if ("/*") { /*
    /* // comment out
  }*/
  }

  //\n

  /*
  This is a multiline
  comment.
  "coomennt"
  */
  printf("all\"night\n");

  printf("allnight\n");
  // This is another multiline \
        comment that spans multiple \
          lines.\no

  if (1 < 2) {
    printf("1 is less than 2\n");
  }

  return 0;
}
