#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long index;
  long sum0;
  long sum1;
  long up;
  long down;
  long left;
  long right;
  long front;
  long back;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        index = i_col + 32L * (j_col + 32L * k_col);
        sum0 = ((long )0);
        sum1 = ((long )0);
        up = i_col + 32L * j_col;
        down = up + 1L;
        left = up - 32L;
        right = down - 32L;
        front = up - 32L * 32L;
        back = front + 32L;
        sum0 += C0 * (orig[up] + orig[down] + orig[left] + orig[right] + orig[front] + orig[back]);
        sum1 += C1 * orig[index];
        sol[index] = sum1 - sum0;
      }
    }
  }
}