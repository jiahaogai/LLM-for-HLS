#pragma ACCEL kernel

void kernel_jacobi_2d(int tsteps,int n,double A[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 39; t++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 1; j < 89; j++) {
        A[i][j] = (A[i][j - 1] + A[i][1 + j] + A[1 + i][j] + A[i][j + 1] + A[j + 1][i] + A[i + 1][j] + A[j][i]) / 8.0;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 89; j++) {
        A[i][j] = A[i][j] - 1.0;
      }
    }
  }
//#pragma endscop
}