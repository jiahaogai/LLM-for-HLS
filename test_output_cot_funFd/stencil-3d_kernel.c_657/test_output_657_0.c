#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1 + 32;j -- > 0 + 1;) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 1 + 32;k_col -- > 0 + 1;) {
      idx = 39304 * (j - 1 + 1) + (k_col - 1 + 1);
      i_col = 32768 * (k_col - 1 + 1);
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1 + 32;i -- > 0 + 1;) {
        tmp = ((C0 * (orig[idx + 39304 * 1] + orig[idx + 39304 * 2])) + (C1 * (orig[idx + 39304 * 3] + orig[idx + 39304 * 4]))) / (C0 + C1);
        sol[i_col + 32768 * 1] = tmp;
        idx++;
        i_col++;
      }
    }
  }
}