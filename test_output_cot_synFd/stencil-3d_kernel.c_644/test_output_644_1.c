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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
  for (j = 1 + 32 - 1; j-- > 1 + 0; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
    for (k = 1 + 32 - 1; k-- > 1 + 0; ) {
      k_col = 32 * k;
      i_col = 32 * j;
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1 + 32 - 1; i-- > 1 + 0; ) {
        idx = i + i_col + ((j + k_col) * 32);
        idx_col = i + i_col;
        TMP_0 = orig[idx_col + 1 + ((k_col + 1) * 32)] + C0;
        TMP_1 = orig[idx_col + 1 + k_col] + C1;
        TMP_2 = orig[idx_col + 1 + ((k_col - 1) * 32)] + C1;
        TMP_3 = orig[idx_col + ((k_col + 1) * 32)] + C0;
        TMP_4 = orig[idx_col + ((k_col - 1) * 32)] + C0;
        TMP_5 = orig[idx_col + 1 + ((k_col + 32) * 32)] + C0;
        TMP_6 = orig[idx_col + 1 + ((k_col - 32) * 32)] + C0;
        TMP_7 = orig[idx_col + ((k_col + 32) * 32)] + C0;
        TMP_8 = orig[idx_col + ((k_col - 32) * 32)] + C0;
        sol[idx] = TMP_0 + TMP_1 + TMP_2 + TMP_3 + TMP_4 + TMP_5 + TMP_6 + TMP_7 + TMP_8;
      }
    }
  }
}