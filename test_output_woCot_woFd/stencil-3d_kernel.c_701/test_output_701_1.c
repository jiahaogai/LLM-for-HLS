#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 0; k < 3; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 3; i++) {
        sol[INDEX(i, j, k)] = ((C0 * orig[INDEX(i - 1, j - 1, k - 1)]) + (C1 * (orig[INDEX(i, j - 1, k - 1)] + orig[INDEX(i + 1, j - 1, k - 1)] + orig[INDEX(i - 1, j, k - 1)] + orig[INDEX(i + 1, j, k - 1)] + orig[INDEX(i - 1, j + 1, k - 1)] + orig[INDEX(i + 1, j + 1, k - 1)] + orig[INDEX(i - 1, j - 1, k)] + orig[INDEX(i + 1, j - 1, k)] + orig[INDEX(i - 1, j, k)] + orig[INDEX(i + 1, j, k)] + orig[INDEX(i - 1, j + 1, k)] + orig[INDEX(i + 1, j + 1, k)] + orig[INDEX(i, j, k - 1)] + orig[INDEX(i, j, k + 1)]))) / (C0 + C1);
      }
    }
  }
//#pragma endscop
}