#pragma ACCEL kernel

void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{118}
    for (i = 1; i < 118; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    B[0] = 0.33333 * (A[0] + A[1] + A[2]);
    
#pragma ACCEL PARALLEL FACTOR=auto{119}
    for (i = 1; i < 118; i++) {
      A[i] = B[i];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    A[0] = 0.33333 * (B[0] + B[1] + B[2]);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    A[118] = 0.33333 * (B[117] + B[118] + B[119]);
  }
//#pragma endscop
}