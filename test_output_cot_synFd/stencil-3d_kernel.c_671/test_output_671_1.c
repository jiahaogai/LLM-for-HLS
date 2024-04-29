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
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0 - 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        bound = (40 * (k - 1)) + j - 1;
        t1 = orig[bound - 1] + orig[bound] + orig[bound + 1];
        bound = (40 * (k - 1)) + j;
        t2 = orig[bound - 1] + orig[bound] + orig[bound + 1];
        bound = (40 * (k - 1)) + j + 1;
        t3 = orig[bound - 1] + orig[bound] + orig[bound + 1];
        sol[k_col * 40 + j_col] = ((t1 + t2) + t3) / 66L;
      }
    }
  }
}