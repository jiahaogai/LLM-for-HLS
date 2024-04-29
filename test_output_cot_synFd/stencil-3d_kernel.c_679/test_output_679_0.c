#pragma ACCEL kernel

void kernel_stencil(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (k = 2; k < 32 + 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 2; j < 32 + 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 2; i < 32 + 2; i++) {
        sol[INDEX(i, j, k)] = ((C0 * sol[INDEX(i - 2, j, k)]) + (C1 * sol[INDEX(i - 1, j, k)]) + (C0 * sol[INDEX(i + 1, j, k)]) + (C1 * sol[INDEX(i + 2, j, k)]) + (C0 * sol[INDEX(i, j - 2, k)]) + (C1 * sol[INDEX(i, j - 1, k)]) + (C0 * sol[INDEX(i, j + 1, k)]) + (C1 * sol[INDEX(i, j + 2, k)]) + (C0 * sol[INDEX(i, j, k - 2)]) + (C1 * sol[INDEX(i, j, k - 1)]) + (C0 * sol[INDEX(i, j, k + 1)]) + (C1 * sol[INDEX(i, j, k + 2)])) / (C0 + C1 + 2);
      }
    }
  }
//#pragma endscop
}