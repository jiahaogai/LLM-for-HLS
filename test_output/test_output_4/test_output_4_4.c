
 #pragma ACCEL kernel

void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 3B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PIPELINE auto{off}
  }
//#pragma endscop
}
2; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{6}
    for (i = 1; i < 119; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 119; i++) {
      