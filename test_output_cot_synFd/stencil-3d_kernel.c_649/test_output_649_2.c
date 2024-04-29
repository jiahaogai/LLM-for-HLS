#pragma ACCEL kernel

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
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 * 1L + k;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40 * k_col + j;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40 * j_col + i;
        sum = ((C0 * orig[i_col]) + (C1 * (orig[i_col + 1] + orig[i_col - 1])));
        sum += orig[i_col + 40] + orig[i_col - 40];
        buf[0] = sum;
        sum = ((C0 * buf[0]) + (C1 * (buf[1] + buf[2])));
        sol[i_col] = sum;
        buf[26] = sum;
        buf[25] = orig[i_col + 160];
        buf[24] = orig[i_col + 128];
        buf[23] = orig[i_col + 96];
        buf[22] = orig[i_col + 64];
        buf[21] = orig[i_col + 32];
        buf[20] = orig[i_col + 8];
        buf[19] = orig[i_col + 24];
        buf[18] = orig[i_col + 40];
        buf[17] = orig[i_col + 56];
        buf[16] = orig[i_col + 80];
        buf[15] = orig[i_col + 112];
        buf[14] = orig[i_col + 144];
        buf[13] = orig[i_col + 176];
        buf[12] = orig[i_col + 208];
        buf[11] = orig[i_col + 240];
        buf[10] = orig[i_col + 272];
        buf[9] = orig[i_col + 304];
        buf[8] = orig[i_col + 336];
        buf[7] = orig[i_col + 368];
        buf[6] = orig[i_col + 400];
        buf[5] = orig[i_col + 432];
        buf[4] = orig[i_col + 464];
        buf[3] = orig[i_col + 496];
        buf[2] = orig[i_col + 528];
        buf[1] = orig[i_col + 560];
      }
    }
  }
}