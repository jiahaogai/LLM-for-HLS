

7. For the function `kernel_jacobi_1d`:
    - Transform this kernel from a sequential kernel to a data-parallel kernel.

8. For the second loop:
    - Automatically pipeline this loop.

9. For the first loop:
    - Partition L1:complete

10. For the first loop:
    - Parallelize sequentially

11. For the second loop:
    - Parallelize with B4 (4)

12. For the first loop:
    - Parallelize with FACTOR=auto{1}

#pragma ACCEL kernel

void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
  }
//#pragma endscop
}
