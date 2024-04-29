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
     k_col = 40 * 1 * 1 + 1 * 1 + k;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40 * 1 + 1 * 1 + j;
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40 * 1 + 1 + i;
        sum = ((orig[i_col - 1] + orig[i_col + 1]) + (orig[i_col - 40] + orig[i_col + 40])) + (orig[i_col - 40 * 40] + orig[i_col + 40 * 40]);
        sum = sum + C0;
        buf[0] = 1 * 40 * 1 + 1 * 1 + 0;
        buf[1] = 1 * 40 * 1 + 1 * 1 + 1;
        buf[2] = 1 * 40 * 1 + 1 * 1 + 40;
        buf[3] = 1 * 40 * 1 + 1 * 1 + 41;
        buf[4] = 1 * 40 * 1 + 1 * 40 + 0;
        buf[5] = 1 * 40 * 1 + 1 * 40 + 1;
        buf[6] = 1 * 40 * 1 + 1 * 40 + 40;
        buf[7] = 1 * 40 * 1 + 1 * 40 + 41;
        buf[8] = 1 * 40 * 1 + 1 * 80 + 0;
        buf[9] = 1 * 40 * 1 + 1 * 80 + 1;
        buf[10] = 1 * 40 * 1 + 1 * 80 + 40;
        buf[11] = 1 * 40 * 1 + 1 * 80 + 41;
        buf[12] = 1 * 40 * 1 + 1 * 120 + 0;
        buf[13] = 1 * 40 * 1 + 1 * 120 + 1;
        buf[14] = 1 * 40 * 1 + 1 * 120 + 40;
        buf[15] = 1 * 40 * 1 + 1 * 120 + 41;
        buf[16] = 1 * 40 * 40 + 1 * 1 + 0;
        buf[17] = 1 * 40 * 40 + 1 * 1 + 1;
        buf[18] = 1 * 40 * 40 + 1 * 1 + 40;
        buf[19] = 1 * 40 * 40 + 1 * 1 + 41;
        buf[20] = 1 * 40 * 40 + 1 * 40 + 0;
        buf[21] = 1 * 40 * 40 + 1 * 40 + 1;
        buf[22] = 1 * 40 * 40 + 1 * 40 + 40;
        buf[23] = 1 * 40 * 40 + 1 * 40 + 41;
        buf[24] = 1 * 40 * 40 + 1 * 80 + 0;
        buf[25] = 1 * 40 * 40 + 1 * 80 + 1;
        buf[26] = 1 * 40 * 40 + 1 * 80 + 40;
        buf[27] = 1 * 40 * 40 + 1 * 80 + 41;
        sum = sum + orig[i_col];
        sol[buf[0]] = sum * C1;
        sol[buf[1]] = sum * C1;
        sol[buf[2]] = sum * C1;
        sol[buf[3]] = sum * C1;
        sol[buf[4]] = sum * C1;
        sol[buf[5]] = sum * C1;
        sol[buf[6]] = sum * C1;
        sol[buf[7]] = sum * C1;
        sol[buf[8]] = sum * C1;
        sol[buf[9]] = sum * C1;
        sol[buf[10]] = sum * C1;
        sol[buf[11]] = sum * C1;
        sol[buf[12]] = sum * C1;
        sol[buf[13]] = sum * C1;
        sol[buf[14]] = sum * C1;
        sol[buf[15]] = sum * C1;
        sol[buf[16]] = sum * C1;
        sol[buf[17]] = sum * C1;
        sol[buf[18]] = sum * C1;
        sol[buf[19]] = sum * C1;
        sol[buf[20]] = sum * C1;
        sol[buf[21]] = sum * C1;
        sol[buf[22]] = sum * C1;
        sol[buf[23]] = sum * C1;
        sol[buf[24]] = sum * C1;
        sol[buf[25]] = sum * C1;
        sol[buf[26]] = sum * C1;
      }
    }
  }
}