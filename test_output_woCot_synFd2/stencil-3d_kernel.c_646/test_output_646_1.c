4. Function Body:
   #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
     k_col = k - 1 + 32 * 4;
     loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      j_col = j - 1 + 32 * 4;
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        i_col = i - 1 + 32 * 4;
        buf[0] = orig[i_col - 1 + j_col - 1 + k_col];
        buf[1] = orig[i_col + j_col - 1 + k_col];
        buf[2] = orig[i_col + 1 + j_col - 1 + k_col];
        buf[3] = orig[i_col - 1 + j_col + k_col];
        buf[4] = orig[i_col + j_col + k_col];
        buf[5] = orig[i_col + 1 + j_col + k_col];
        buf[6] = orig[i_col - 1 + j_col - 1 + k_col + 32];
        buf[7] = orig[i_col + j_col - 1 + k_col + 32];
        buf[8] = orig[i_col + 1 + j_col - 1 + k_col + 32];
        buf[9] = orig[i_col - 1 + j_col + k_col + 32];
        buf[10] = orig[i_col + j_col + k_col + 32];
        buf[11] = orig[i_col + 1 + j_col + k_col + 32];
        buf[12] = orig[i_col - 1 + j_col - 1 + k_col + 32 * 2];
        buf[13] = orig[i_col + j_col - 1 + k_col + 32 * 2];
        buf[14] = orig[i_col + 1 + j_col - 1 + k_col + 32 * 2];
        buf[15] = orig[i_col - 1 + j_col + k_col + 32 * 2];
        buf[16] = orig[i_col + j_col + k_col + 32 * 2];
        buf[17] = orig[i_col + 1 + j_col + k_col + 32 * 2];
        buf[18] = orig[i_col - 1 + j_col - 1 + k_col + 32 * 3];
        buf[19] = orig[i_col + j_col - 1 + k_col + 32 * 3];
        buf[20] = orig[i_col + 1 + j_col - 1 + k_col + 32 * 3];
        buf[21] = orig[i_col - 1 + j_col + k_col + 32 * 3];
        buf[22] = orig[i_col + j_col + k_col + 32 * 3];
        buf[23] = orig[i_col + 1 + j_col + k_col + 32 * 3];
        buf[24] = orig[i_col - 1 + j_col - 1 + k_col + 32 * 4];
        buf[25] = orig[i_col + j_col - 1 + k_col + 32 * 4];
        buf[26] = orig[i_col + 1 + j_col - 1 + k_col + 32 * 4];
        buf[27] = orig[i_col - 1 + j_col + k_col + 32 * 4];
        buf[28] = orig[i_col + j_col + k_col + 32 * 4];
        buf[29] = orig[i_col + 1 + j_col + k_col + 32 * 4];
        sol[i_col - 1 + j_col - 1 + k_col] = ((C0 * buf[0]) + (C1 * buf[1])) + ((C0 * buf[2]) + (C1 * buf[3])) + ((C0 * buf[4]) + (C1 * buf[5])) + ((C0 * buf[6]) + (C1 * buf[7])) + ((C0 * buf[8]) + (C1 * buf[9])) + ((C1 * buf[10]) + (C0 * buf[11])) + ((C1 * buf[12]) + (C0 * buf[13])) + ((C1 * buf[14]) + (C0 * buf[15])) + ((C1 * buf[16]) + (C0 * buf[17])) + ((C1 * buf[18]) + (C0 * buf[19])) + ((C1 * buf[20]) + (C0 * buf[21])) + ((C1 * buf[22]) + (C0 * buf[23])) + ((C1 * buf[24]) + (C0 * buf[25])) + ((C1 * buf[26]) + (C0 * buf[27])) + ((C1 * buf[28]) + (C0 * buf[29]));
      }
    }
  }
}