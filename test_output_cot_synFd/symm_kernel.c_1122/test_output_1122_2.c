__Note:__The `__restrict__` qualifier is used to mark restrictions to the compiler. In this application, the `__restrict__` qualifiers are used to indicate that the pointers pointing to the respective matrices do not alias. Aliasing is a problem because even though the two matrices are disjoint (they do not overlap), the compiler cannot know this for sure. Using the `__restrict__` qualifiers allows the compiler to make optimized code.

#include <math.h>
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        int _in_j = 0;
        int _in_k = 0;
        for (_in_k = 0; _in_k < 60; _in_k++) {
          temp2 += A[i][_in_k] * B[_in_k][j];
        }
        mult = alpha * temp2;
        C[i][j] += mult;
      }
    }
  }
  
#pragma endscop
}