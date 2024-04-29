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
  long TMP_0;
  long TMP_1;
  long TMP_2;
  long TMP_3;
  long TMP_4;
  long TMP_5;
  long TMP_6;
  long TMP_7;
  long TMP_8;
  long TMP_9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1; j <= 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1;k++) {...} */
    for (k = 1; k <= 32; k++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
/* Standardize from: for(i = 1;i < 393216;i++) {...} */
      for (i = 1; i <= 393216; i++) {
        k_col = ((32 + 1) * (k - 1)) + 1;
        i_col = ((32 + 1) * (i - 1)) + 1;
        idx = i_col + k_col;
        idx_col = i_col - 1 + k_col;
        TMP_0 = orig[idx_col + -1] + ((C0 * orig[idx_col + -32]) + (C1 * orig[idx_col])) + orig[idx_col + 32];
        TMP_1 = orig[idx_col + -32] + ((C0 * TMP_0) + (C1 * orig[idx_col])) + orig[idx_col + 32];
        TMP_2 = orig[idx_col] + ((C0 * orig[idx_col + -1]) + (C1 * TMP_1)) + orig[idx_col + 1];
        TMP_3 = orig[idx_col + 32] + ((C0 * TMP_2) + (C1 * orig[idx_col])) + orig[idx_col + 33];
        TMP_4 = TMP_1 + ((C0 * TMP_2) + (C1 * TMP_3));
        TMP_5 = TMP_0 + ((C0 * orig[idx_col]) + (C1 * TMP_4));
        TMP_6 = TMP_3 + ((C0 * TMP_4) + (C1 * orig[idx_col + 33]));
        sol[idx] = TMP_5;
        sol[idx + 32768] = TMP_6;
      }
    }
  }
}