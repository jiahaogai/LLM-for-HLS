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
  long delta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = orig[i + 40L * (j + 40L * k)] ;
        delta = buf - ((orig[i_col + 40L * (j_col + 40L * k_col)] + orig[i_col + 40L * (j + 40L * k_col)] + orig[i_col + 40L * (j_col + 40L * k)] + orig[i + 40L * (j_col + 40L * k_col)] + orig[i + 40L * (j + 40L * k_col)] + orig[i + 40L * (j_col + 40L * k)]) / 6L);
        sol[i + 40L * (j + 40L * k)] = delta;
      }
    }
  }
}