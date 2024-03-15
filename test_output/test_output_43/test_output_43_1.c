 Don't automatically pipeline the third loop. Pipeline the fourth loop with off
pragma ACCEL kernel

void kernel_jacobi_2d(int tsteps,int n,double A[90][90],double B[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 89; j++) {
        B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[i - 1][j] + A[i - 1][j - 1] + A[i - 1][1 + j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 89; j++) {
        A[i][j] = 0.2 * (B[i][j] + B[i][j - 1] + B[i][1 + j] + B[i - 1][j] + B[i - 1][j - 1] + B[i - 1][1 + j]);
      }
    }
  }
//#pragma endscop
}
