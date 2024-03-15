#pragma ACCEL kernel

void kernel_heat_3d(int tsteps,int n,double A[60][60],double B[60][60])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 1; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      for (j = 1; j < 59; j++) {
        A[i][j] = 0.2 * (A[i - 1][j] + A[i + 1][j] + A[i][j - 1] + A[i][j + 1] + A[i][j]) + 0.6 * A[i][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      for (j = 1; j < 59; j++) {
        B[i][j] = 0.2 * (B[i - 1][j] + B[i + 1][j] + B[i][j - 1] + B[i][j + 1] + B[i][j]) + 0.6 * B[i][j];
      }
    }
  }
//#pragma endscop
}