 Don't automatically pipeline the third loop. Pipeline the fourth loop.
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
  for (t = 0; t < 3{
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 1; j < 89; j++) {
      B[i][j] = 0.33333 * (A[i][j - 1] + A[i][j] + A[i][j + 1]);
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (t = 0; t < 390; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 89; i++) {
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 89; j++) {
        A[i][j] = 0.33333 * (B[i][j - 1] + B[i][j] + B[i][j + 1]);
      }
    }
  }
//#pragma endscop
}
