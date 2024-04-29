#pragma ACCEL kernel

void stencil3d(int C0,int C1,double orig[27],double sol[27])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 0; k < 3; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        sol[INDEX(i, j, k)] = ((double )0);
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (idx = 0; idx < 27; ++idx) {
          sol[INDEX(i, j, k)] += orig[idx] * ((double )3.141592653589793) * ((double )((double )3.141592653589793) * ((double )((double )3.141592653589793) * (((double )(((double )3) * (i - 1)) * (i - 1)) + (((double )3) * (j - 1)) * (j - 1)) + (k - 1) * (k - 1)));
        }
      }
    }
  }
//#pragma endscop
}