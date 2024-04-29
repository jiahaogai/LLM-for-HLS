Code: 
#pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: 
#pragma ACCEL TILE FACTOR=auto{8}
Error: 
Please check the code and try again.
Code: 
#pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: 
#include <math.h>
Error: 
Please check the code and try again.
Code: 
#define N 8192
Error: 
Please check the code and try again.
Code: 
#define P 1
Error: 
Please check the code and try again.
Code: 
void stencil(int orig[8192],int sol[8192],int filter[9])
Error: 
Please check the code and try again.
Code: {
Error: 
Please check the code and try again.
Code: int i;
Error: 
Please check the code and try again.
Code: int j;
Error: 
Please check the code and try again.
Code: int k;
Error: 
Please check the code and try again.
Code: int tmp;
Error: 
Please check the code and try again.
Code: 
//#pragma scop
Error: 
Please check the code and try again.
Code: i = 0;
Error: 
Please check the code and try again.
Code: while (i < 8192) {
Error: 
Please check the code and try again.
Code: tmp = 0;
Error: 
Please check the code and try again.
Code: j = 0;
Error: 
Please check the code and try again.
Code: while (j < 9) {
Error: 
Please check the code and try again.
Code: tmp += filter[j] * orig[i + j - 4];
Error: 
Please check the code and try again.
Code: j++;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: sol[i] = tmp;
Error: 
Please check the code and try again.
Code: i++;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: //#pragma endscop
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.