#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 392 * 0; j < 392 + 392 * 0; j += 392 * 0) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 392 * 0; k < 392 + 392 * 0; k += 392 * 0) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 392 * 0; i < 392 + 392 * 0; i += 392 * 0) {
        i_col = i - 1 + 392 * (k - 1);
        k_col = k - 1 + 392 * (j - 1);
        j_col = j - 1;
        bound = (k > 1) ? -1 : 0;
        t = orig[i_col + 392 * bound] + orig[k_col + 392 * (-1)] + orig[j_col + 392 * (-1)] + orig[k_col + 392 * 0] + orig[j_col + 392 * 0] + orig[k_col + 392 * 1] + orig[j_col + 392 * 1] + orig[k_col + 392 * 2];
        sol[i_col] = t;
      }
    }
  }
}