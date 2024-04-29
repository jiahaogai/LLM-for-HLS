#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
     k_col = k;
     i_col = 2;
     loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
      j_col = j;
      i_row = i_col;
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        j_row = j_col;
        i_row = i_row + 1;
        idx = i_row * (130 - 2) + j_row;
        idx_col = i_col * (130 - 2) + j_col;
        idx_row = i_row * (130 - 2) + j_row;
        t = ((((50 * (orig[idx_col + 1] + orig[idx_col - 1]) + 
                2 * (orig[idx_col] + orig[idx_row]) + 
                50 * (orig[idx_row + 1] + orig[idx_row - 1])) / 116) - 
                orig[idx]) / 1.0E-6);
        if (t < -127) {
          t = -127;
        }
         else if (t > 127) {
          t = 127;
        }
         sol[idx] = t + orig[idx];
      }
      i_col = i_col + 1;
    }
    k_row = k_col;
  }
}