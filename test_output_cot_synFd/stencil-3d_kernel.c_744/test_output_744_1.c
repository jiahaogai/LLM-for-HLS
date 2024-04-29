#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      k_col = 392 - k;
      i_col = 392 - j;
      idx = i_col * 392 + k_col;
      idx_col = k_col * 392 + i_col;
      C0_idx = idx * 2;
      C1_idx = C0_idx + 1;
      tmp = ((C0 * ((long )orig[C0_idx])) + (C1 * ((long )orig[C1_idx]))) + ((long )orig[idx]);
      sol[idx] = tmp;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
      for (i = 1; i < 392 + 1; i++) {
        idx = i * 392 + k_col;
        C0_idx = idx * 2;
        C1_idx = C0_idx + 1;
        tmp = ((C0 * ((long )orig[C0_idx])) + (C1 * ((long )orig[C1_idx]))) + ((long )orig[idx]);
        sol[idx] = tmp;
      }
    }
  }
}