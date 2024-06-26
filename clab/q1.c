#include <stdio.h>
#include <stdlib.h>

#define MAX_INTS 6

int main() {
  int source[MAX_INTS];
  int j;
  
  for (j = 0; j < MAX_INTS; j++)
    if (scanf("%d", source + j) == EOF) {
      printf("Too few values!\n");
      exit(1);
    }

  printf("%s\n%.16f\n", (char*)source, *(double*)(source+4));
 
  return 0;
}
