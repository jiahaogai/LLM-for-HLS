void kernel_jacobi_2d(int tsteps,int n,double A[90][90],double B[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 39; t++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 89; j++) {
        A[i][j] = 0.2 * (A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1] + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1] + A[i + 1][j] + A[i + 1][j + 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 89; j++) {
        B[i][j] = 0.2 * (A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1] + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1] + A[i + 1][j] + A[i + 1][j + 1]);
      }
    }
  }
//#pragma endscop
}