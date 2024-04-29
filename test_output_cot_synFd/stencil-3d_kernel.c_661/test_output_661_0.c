#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  setup:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    k_col:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      j_col:
      for (i = 0; i < 40; i++) {
        i_col = i - 1;
        if (i == 0) {
          i_col = i;
        }
        j_col = j - 1;
        if (j == 0) {
          j_col = j;
        }
        k_col = k - 1;
        if (k == 0) {
          k_col = k;
        }
        bound = (k_col * 40 + j_col) * 40 + i_col;
        t = orig[bound] + 
          + ((long )1) * (orig[bound + 1] + orig[bound + 40] + orig[bound + 40 * 2] + orig[bound + 40 * 3])
          + ((long )2) * (orig[bound + 40 * 4] + orig[bound + 40 * 5] + orig[bound + 40 * 6] + orig[bound + 40 * 7])
          + ((long )3) * (orig[bound + 40 * 8] + orig[bound + 40 * 9] + orig[bound + 40 * 10] + orig[bound + 40 * 11])
          + ((long )4) * (orig[bound + 40 * 12] + orig[bound + 40 * 13] + orig[bound + 40 * 14] + orig[bound + 40 * 15])
          + ((long )5) * (orig[bound + 40 * 16] + orig[bound + 40 * 17] + orig[bound + 40 * 18] + orig[bound + 40 * 19])
          + ((long )6) * (orig[bound + 40 * 20] + orig[bound + 40 * 21] + orig[bound + 40 * 22] + orig[bound + 40 * 23])
          + ((long )7) * (orig[bound + 40 * 24] + orig[bound + 40 * 25] + orig[bound + 40 * 26] + orig[bound + 40 * 27])
          + ((long )8) * (orig[bound + 40 * 28] + orig[bound + 40 * 29] + orig[bound + 40 * 30] + orig[bound + 40 * 31])
          + ((long )9) * (orig[bound + 40 * 32] + orig[bound + 40 * 33] + orig[bound + 40 * 34] + orig[bound + 40 * 35])
          + ((long )10) * (orig[bound + 40 * 36] + orig[bound + 40 * 37] + orig[bound + 40 * 38] + orig[bound + 40 * 39]);
        sol[bound] = ((t + 4096) / 8192);
      }
    }
  }
}