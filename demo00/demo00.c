#include<stdio.h>
#include<math.h>

void example1(){
  int x1 = 40000;
  int x2 = 50000;
  printf("40000^2 = %d\n", x1*x1);
  printf("50000^2 = %d\n", x2*x2);

}

void example2(){
  float a = pow(2,30);
  float b = -1*a;
  float c = 3.14;

  printf("(2^30 + -2^30) + 3.14 = %f\n", (a + b) + c);
  printf("2^30 + (2^30 + 3.14) = %f\n", a + (b + c));
}

int sum_interval(int k, int s){
  if(s >= k){
    int total = 0;
    for(; k < s+1;){
      total = total + k;
      k++;
    }
    return total;
  } else {
    return -1;
  }

  
}

void exercise1(){
  int x = sum_interval(13, 47);
  printf("%d\n",x);
}

int main(int argc, char** argv){
  //example1();
  //example2();
  
  exercise1();
  
  return 0;
}
