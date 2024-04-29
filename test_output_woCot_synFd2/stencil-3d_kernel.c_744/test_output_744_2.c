#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long index;
  long k_row;
  long i_row;
  long j_row;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k_row = 1; k_row <= 32 - 2; k_row++) {
    k = k_row + 1;
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j_row = 1; j_row <= 32 - 1; j_row++) {
      j = j_row + 1;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i_row = 1; i_row <= 32 - 1; i_row++) {
        i = i_row + 1;
        i_col = i - 1 + ((j - 1) * (32L));
        j_col = j - 1 + ((k - 1) * (32L));
        k_col = k - 1 + ((i - 1) * (32L));
        index = i_col + ((j_col * 32L) + (k_col * (32L) * 32L));
        tmp = ((C0 * (orig[index - 1 - (32L) - (32L)] + orig[index - 1 - (32L) + 1] + orig[index - 1 + 1] + orig[index - 1 + (32L)])) + (C1 * (orig[index + 1 - (32L) - 1] + orig[index + 1 - (32L)] + orig[index + 1 - (32L) + 1] + orig[index + 1 + 1] + orig[index + 1 + (32L)] + orig[index + 1 + (32L) + 1] + orig[index + 1 + (32L) - 1] + orig[index + 1])));
        sol[index] = tmp;
      }
    }
  }
}