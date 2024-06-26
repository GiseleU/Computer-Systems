#include <stdio.h>
#include <stdlib.h>

int main() {
  
  int x = 47;
  int* ptr = &x;
  char* ptr2 = (char*) ptr;
  int y = *ptr;
  char c = *ptr2;

  printf(y);
  printf(c);
  return 0;
}