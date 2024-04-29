void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j-- > 32 + 1; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i-- > 32 + 1; ) {
        i_col = i - 1 + (-1 * 32);
        j_col = j - 1 + (-1 * 32);
        k_col = k - 1 + (-1 * 32);
        sum = 0;
        buf[0] = orig[i_col + 32 * (j_col + 32 * k_col)];
        buf[1] = orig[i_col + 1 + 32 * (j_col + 32 * k_col)];
        buf[2] = orig[i_col + 2 + 32 * (j_col + 32 * k_col)];
        buf[3] = orig[i_col + 3 + 32 * (j_col + 32 * k_col)];
        buf[4] = orig[i_col + 32 * (j_col + 1 + 32 * k_col)];
        buf[5] = orig[i_col + 1 + 32 * (j_col + 1 + 32 * k_col)];
        buf[6] = orig[i_col + 2 + 32 * (j_col + 1 + 32 * k_col)];
        buf[7] = orig[i_col + 3 + 32 * (j_col + 1 + 32 * k_col)];
        buf[8] = orig[i_col + 32 * (j_col + 2 + 32 * k_col)];
        buf[9] = orig[i_col + 1 + 32 * (j_col + 2 + 32 * k_col)];
        buf[10] = orig[i_col + 2 + 32 * (j_col + 2 + 32 * k_col)];
        buf[11] = orig[i_col + 3 + 32 * (j_col + 2 + 32 * k_col)];
        buf[12] = orig[i_col + 32 * (j_col + 3 + 32 * k_col)];
        buf[13] = orig[i_col + 1 + 32 * (j_col + 3 + 32 * k_col)];
        buf[14] = orig[i_col + 2 + 32 * (j_col + 3 + 32 * k_col)];
        buf[15] = orig[i_col + 3 + 32 * (j_col + 3 + 32 * k_col)];
        buf[16] = orig[i_col + 32 * (j_col + 1 + 32 * k_col + 1)];
        buf[17] = orig[i_col + 1 + 32 * (j_col + 1 + 32 * k_col + 1)];
        buf[18] = orig[i_col + 2 + 32 * (j_col + 1 + 32 * k_col + 1)];
        buf[19] = orig[i_col + 3 + 32 * (j_col + 1 + 32 * k_col + 1)];
        buf[20] = orig[i_col + 32 * (j_col + 2 + 32 * k_col + 1)];
        buf[21] = orig[i_col + 1 + 32 * (j_col + 2 + 32 * k_col + 1)];
        buf[22] = orig[i_col + 2 + 32 * (j_col + 2 + 32 * k_col + 1)];
        buf[23] = orig[i_col + 3 + 32 * (j_col + 2 + 32 * k_col + 1)];
        buf[24] = orig[i_col + 32 * (j_col + 3 + 32 * k_col + 1)];
        buf[25] = orig[i_col + 1 + 32 * (j_col + 3 + 32 * k_col + 1)];
        buf[26] = orig[i_col + 2 + 32 * (j_col + 3 + 32 * k_col + 1)];
        buf[27] = orig[i_col + 3 + 32 * (j_col + 3 + 32 * k_col + 1)];
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk_1:
        for (k_1 = 0; k_1 < 28; k_1++) {
          sum += buf[k_1] * 32;
        }
        sol[i + 32 * (j + 32 * k)] = sum;
      }
    }
  }
}