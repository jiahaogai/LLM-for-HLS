Code: }
Error: 
Please check the code and try again.
Code: 
#pragma ACCEL kernel

void stencil(int n,double A[400][400],double B[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_i:
  for (i = 1; i < 398; i++) {
     loop_j:
    for (j = 1; j < 398; j++) {
      A[i][j] = 0.2 * ( B[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j] );
    }
  }
}
Error: 
Please check the code and try again.
Code: }