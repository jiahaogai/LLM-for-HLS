#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long upper_bound;
  long lower_bound;
  long r;
  long q;
  long p;
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40 - k;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40 - j;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 40 - i;
        upper_bound = ((((i_col + 2) < 40) ? (i_col + 2) : 40)) - 1;
        lower_bound = ((2 + i_col) > 0 ? 2 + i_col : 0);
        sum = 0.0;
        loop_r:
        for (r = lower_bound; r <= upper_bound; r++) {
          loop_q:
          for (q = lower_bound; q <= upper_bound; q++) {
            loop_p:
            for (p = lower_bound; p <= upper_bound; p++) {
              idx = ((((((i * 40) + j) * 40) + k) * 3) + 0) + r;
              sum += ((orig[idx] * C0) + (orig[idx + 1] * C1));
            }
          }
        }
        sol[(((((i * 40) + j) * 40) + k) * 1)] = sum;
      }
    }
  }
}