#include <stdio.h>
#include <stdlib.h>

int main() {

// char string[] = "n";
double pi = 3.1415926535897931;
double * ptr1 = &pi;
// char* ptr = &string;
// int * ptr = &pi;

int* ptr = ((int*) ptr1);
int* ptr2 = ((int*) ptr+1);

// int x = *ptr;

// int y = *(ptr + 1);

  printf("%d\n%d", ptr[0], ptr2[0]);
  //("%d", (int*) string);
//   ("%s\n%.16f\n", (char*)string, *(double*)(string+4));
 
  return 0;
}