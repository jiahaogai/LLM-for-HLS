#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 1; i < 32 + 1; i++) {
        sol[INDEX(i, j, k)] = ((C0 * sol[INDEX(i - 1, j, k)]) + (C1 * sol[INDEX(i + 1, j, k)]) + (C0 * sol[INDEX(i, j - 1, k)]) + (C1 * sol[INDEX(i, j + 1, k)]) + (C0 * sol[INDEX(i, j, k - 1)]) + (C1 * sol[INDEX(i, j, k + 1)]) + (C1 * orig[INDEX(i, j, k)])) / (C0 + C1 + 1);
      }
    }
  }
//#pragma endscop
}