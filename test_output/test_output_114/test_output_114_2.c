
 #pragma ACCEL kernel

void kernel_jacobi_2d(int tsteps,int n,double A[90][90],double B[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 90; t++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (i = 1; i < 90 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 1; j < 90 - 1; j++) {
        B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[j][j - 1] + A[j][1 + j] + A[1 + i][j] + A[i - 1][j] + A[1 + i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 90 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 1; j < 90 - 1; j++) {
        A[i][j] = 0.2 * (B[i][j] + B[i][j - 1] + B[i][1 + j] + B[j][j - 1] + B[j][1 + j] + B[1 + i][j] + B[i - 1][j] + B[1 + i][j - 1]);
      }
    }
  }
//#pragma endscop
}
