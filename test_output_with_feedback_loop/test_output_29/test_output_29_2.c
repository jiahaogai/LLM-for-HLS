#pragma ACCEL kernel

void kernel_3d(int tsteps,int n,double A[20][20][20],double B[20][20][20])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 20; t++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 1; i < 20 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 1; j < 20 - 1; j++) {
        for (k = 1; k < 20 - 1; k++) {
          B[i][j][k] = 0.2 * (A[i][j][k] - 0.13 * (A[i][j][k - 1] + A[i][j][k + 1] + A[i][j - 1][k] + A[i][j + 1][k] + A[i - 1][j][k] + A[i + 1][j][k]));
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (i = 1; i < 20 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      for (j = 1; j < 20 - 1; j++) {
        for (k = 1; k < 20 - 1; k++) {
          A[i][j][k] = 0.2 * (B[i][j][k] - 0.13 * (B[i][j][k - 1] + B[i][j][k + 1] + B[i][j - 1][k] + B[i][j + 1][k] + B[i - 1][j][k] + B[i + 1][j][k]));
        }
      }
    }
  }
//#pragma endscop
}