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
        sol[idx + 0] = TMP_0;
        sol[idx + 1] = TMP_1;
        sol[idx + 2] = TMP_2;
        sol[idx + 3] = TMP_3;
        sol[idx + 4] = TMP_4;
        sol[idx + 5] = TMP_5;
        sol[idx + 6] = TMP_6;
        sol[idx + 7] = TMP_7;
        sol[idx + 8] = TMP_8;
        sol[idx + 9] = TMP_9;
        TMP_0 = C1 * (orig[idx_col + 32 + 1 + 0] + orig[idx_col + 32 + 0 + 0]);
        TMP_1 = C1 * (orig[idx_col + 32 + 1 + 1] + orig[idx_col + 32 + 0 + 1]);
        TMP_2 = C1 * (orig[idx_col + 32 + 1 + 2] + orig[idx_col + 32 + 0 + 2]);
        TMP_3 = C1 * (orig[idx_col + 32 + 1 + 3] + orig[idx_col + 32 + 0 + 3]);
        TMP_4 = C1 * (orig[idx_col + 32 + 1 + 4] + orig[idx_col + 32 + 0 + 4]);
        TMP_5 = C1 * (orig[idx_col + 32 + 1 + 5] + orig[idx_col + 32 + 0 + 5]);
        TMP_6 = C1 * (orig[idx_col + 32 + 1 + 6] + orig[idx_col + 32 + 0 + 6]);
        TMP_7 = C1 * (orig[idx_col + 32 + 1 + 7] + orig[idx_col + 32 + 0 + 7]);
        TMP_8 = C1 * (orig[idx_col + 32 + 1 + 8] + orig[idx_col + 32 + 0 + 8]);
        TMP_9 = C1 * (orig[idx_col + 32 + 1 + 9] + orig[idx_col + 32 + 0 + 9]);
        sol[idx + 10] = TMP_0;
        sol[idx + 11] = TMP_1;
        sol[idx + 12] = TMP_2;
        sol[idx + 13] = TMP_3;
        sol[idx + 14] = TMP_4;
        sol[idx + 15] = TMP_5;
        sol[idx + 16] = TMP_6;
        sol[idx + 17] = TMP_7;
        sol[idx + 18] = TMP_8;
        sol[idx + 19] = TMP_9;
        TMP_0 = C1 * (orig[idx_col + 32 + 2 + 0] + orig[idx_col + 32 + 0 + 0]);
        TMP_1 = C1 * (orig[idx_col + 32 + 2 + 1] + orig[idx_col + 32 + 0 + 1]);
        TMP_2 = C1 * (orig[idx_col + 32 + 2 + 2] + orig[idx_col + 32 + 0 + 2]);
        TMP_3 = C1 * (orig[idx_col + 32 + 2 + 3] + orig[idx_col + 32 + 0 + 3]);
        TMP_4 = C1 * (orig[idx_col + 32 + 2 + 4] + orig[idx_col + 32 + 0 + 4]);
        TMP_5 = C1 * (orig[idx_col + 32 + 2 + 5] + orig[idx_col + 32 + 0 + 5]);
        TMP_6 = C1 * (orig[idx_col + 32 + 2 + 6] + orig[idx_col + 32 + 0 + 6]);
        TMP_7 = C1 * (orig[idx_col + 32 + 2 + 7] + orig[idx_col + 32 + 0 + 7]);
        TMP_8 = C1 * (orig[idx_col + 32 + 2 + 8] + orig[idx_col + 32 + 0 + 8]);
        TMP_9 = C1 * (orig[idx_col + 32 + 2 + 9] + orig[idx_