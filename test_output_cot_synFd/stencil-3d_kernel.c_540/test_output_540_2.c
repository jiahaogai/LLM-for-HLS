#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long tmp;
  long tmp_row;
  long tmp_col;
  long idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        idx = (((32 + 1) * (32 + 1)) * k) + (((32 + 1) * j) + i);
        tmp_col = (((32 + 1) * (32 + 1)) * (k - 1)) + (((32 + 1) * j) + i);
        tmp_row = (((32 + 1) * (32 + 1)) * k) + (((32 + 1) * (j - 1)) + i);
        tmp = orig[tmp_col] + orig[tmp_row] - \
          orig[tmp_col + 1] - orig[tmp_row + 1];
        buf = ((C0 * tmp) + (C1 * sol[idx - 1])) / (C0 + C1);
        sol[idx] = buf;
      }
    }
  }
}