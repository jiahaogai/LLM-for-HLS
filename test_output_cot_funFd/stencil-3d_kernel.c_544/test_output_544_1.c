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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    ql_j_1:
    j_col = 392 * 4 * 4 + 4 * 4 - 1 + -4 * 4 + (j - 1) * (4 * 4);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 4;k++) {...} */
    for (k = 1; k < 4 + 1; k++) {
      ql_k_1:
      k_col = 4 * 4 + 4 - 1 + -1 + (k - 1) * (4);
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      
#pragma ACCEL PIPELINE auto{off}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        ql_i_1:
        i_col = i * 4 * 4 + 4 * 4 - 1;
        buf = orig[i_col + 0 + k_col] + orig[i_col + 1 + k_col] + orig[i_col + 2 + k_col] + orig[i_col + 3 + k_col];
        sol[i_col + k_col] = buf;
      }
    }
  }
}