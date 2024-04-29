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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      k_col = 32 * k;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1; i++) {
        i_col = 32 * i;
        idx = i_col + k_col;
        idx_col = k_col + 32;
        TMP_0 = C0 * (orig[idx_col + 1 + 0] + orig[idx_col + 0 + 0]);
        TMP_1 = C0 * (orig[idx_col + 1 + 1] + orig[idx_col + 0 + 1]);
        TMP_2 = C0 * (orig[idx_col + 1 + 2] + orig[idx_col + 0 + 2]);
        TMP_3 = C0 * (orig[idx_col + 1 + 3] + orig[idx_col + 0 + 3]);
        TMP_4 = C0 * (orig[idx_col + 1 + 4] + orig[idx_col + 0 + 4]);
        TMP_5 = C0 * (orig[idx_col + 1 + 5] + orig[idx_col + 0 + 5]);
        TMP_6 = C0 * (orig[idx_col + 1 + 6] + orig[idx_col + 0 + 6]);
        TMP_7 = C0 * (orig[idx_col + 1 + 7] + orig[idx_col + 0 + 7]);
        TMP_8 = C0 * (orig[idx_col + 1 + 8] + orig[idx_col + 0 + 8]);
        TMP_9 = C0 * (orig[idx_col + 1 + 9] + orig[idx_col + 0 + 9]);
        TMP_10 = C0 * (orig[idx_col + 1 + 10] + orig[idx_col + 0 + 10]);
        TMP_11 = C0 * (orig[idx_col + 1 + 11] + orig[idx_col + 0 + 11]);
        TMP_12 = C0 * (orig[idx_col + 1 + 12] + orig[idx_col + 0 + 12]);
        TMP_13 = C0 * (orig[idx_col + 1 + 13] + orig[idx_col + 0 + 13]);
        TMP_14 = C0 * (orig[idx_col + 1 + 14] + orig[idx_col + 0 + 14]);
        TMP_15 = C0 * (orig[idx_col + 1 + 15] + orig[idx_col + 0 + 15]);
        TMP_16 = C0 * (orig[idx_col + 1 + 16] + orig[idx_col + 0 + 16]);
        TMP_17 = C0 * (orig[idx_col + 1 + 17] + orig[idx_col + 0 + 17]);
        TMP_18 = C0 * (orig[idx_col + 1 + 18] + orig[idx_col + 0 + 18]);
        TMP_19 = C0 * (orig[idx_col + 1 + 19] + orig[idx_col + 0 + 19]);
        TMP_20 = C0 * (orig[idx_col + 1 + 20] + orig[idx_col + 0 + 20]);
        TMP_21 = C0 * (orig[idx_col + 1 + 21] + orig[idx_col + 0 + 21]);
        TMP_22 = C0 * (orig[idx_col + 1 + 22] + orig[idx_col + 0 + 22]);
        TMP_23 = C0 * (orig[idx_col + 1 + 23] + orig[idx_col + 0 + 23]);
        TMP_24 = C0 * (orig[idx_col + 1 + 24] + orig[idx_col + 0 + 24]);
        TMP_25 = C0 * (orig[idx_col + 1 + 25] + orig[idx_col + 0 + 25]);
        TMP_26 = C0 * (orig[idx_col + 1 + 26] + orig[idx_col + 0 + 26]);
        TMP_27 = C0 * (orig[idx_col + 1 + 27] + orig[idx_col + 0 + 27]);
        TMP_28 = C0 * (orig[idx_col + 1 + 28] + orig[idx_col + 0 + 28]);
        TMP_29 = C0 * (orig[idx_col + 1 + 29] + orig[idx_col + 0 + 29]);
        TMP_30 = C0 * (orig[idx_col + 1 + 30] + orig[idx_col + 0 + 30]);
        TMP_31 = C0 * (orig[idx_col + 1 + 31] + orig[idx_col + 0 + 31]);
        TMP_32 = C1 * (TMP_0 + TMP_1 + TMP_2 + TMP_3 + TMP_4 + TMP_5 + TMP_6 + TMP_7 + TMP_8 + TMP_9 + TMP_10 + TMP_11 + TMP_12 + TMP_13 + TMP_14 + TMP_15 + TMP_16 + TMP_17 + TMP_18 + TMP_19 + TMP_20 + TMP_21 + TMP_22 + TMP_23 + TMP_24 + TMP_25 + TMP_26 + TMP_27 + TMP_28 + TMP_29 + TMP_30 + TMP_31);
        sol[idx] = TMP_32;
      }
    }
  }
}