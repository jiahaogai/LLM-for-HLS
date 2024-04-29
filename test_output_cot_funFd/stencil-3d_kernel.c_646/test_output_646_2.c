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
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1 + 16L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = j - 1 + 16L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        i_col = i - 1 + 16L;
        sum = ((orig[i_col + j_col * 39 + k_col * 39 * 32] + orig[i_col + 1 + j_col * 39 + k_col * 39 * 32]) + orig[i_col + (j_col - 1) * 39 + k_col * 39 * 32]) + ((orig[i_col + j_col * 39 + (k_col - 1) * 39 * 32] + orig[i_col + 1 + j_col * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + (j_col - 1) * 39 + (k_col - 1) * 39 * 32]);
        sum /= 8L;
        buf[0] = sum;
        sum = ((sum + orig[i_col + 1 + (j_col - 1) * 39 + k_col * 39 * 32]) + orig[i_col + (j_col - 1) * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + 1 + (j_col - 1) * 39 + (k_col - 1) * 39 * 32];
        sum /= 8L;
        buf[1] = sum;
        sum = ((sum + orig[i_col + (j_col - 1) * 39 + k_col * 39 * 32]) + orig[i_col + (j_col - 1) * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + (j_col - 1) * 39 + (k_col - 1) * 39 * 32];
        sum /= 8L;
        buf[2] = sum;
        sum = ((sum + orig[i_col + 1 + j_col * 39 + k_col * 39 * 32]) + orig[i_col + j_col * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + 1 + j_col * 39 + (k_col - 1) * 39 * 32];
        sum /= 8L;
        buf[3] = sum;
        sum = ((sum + orig[i_col + j_col * 39 + k_col * 39 * 32]) + orig[i_col + j_col * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + j_col * 39 + (k_col - 1) * 39 * 32];
        sum /= 8L;
        buf[4] = sum;
        sum = ((sum + orig[i_col + 1 + j_col * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + j_col * 39 + (k_col - 1) * 39 * 32]) + orig[i_col + 1 + j_col * 39 + (k_col - 1) * 39 * 32];
        sum /= 8L;
        buf[5] = sum;
        sum = buf[0];
        sum += buf[1];
        sum += buf[2];
        sum += buf[3];
        sum += buf[4];
        sum += buf[5];
        sol[i_col + j_col * 32 + k_col * 32 * 39] = sum;
      }
    }
  }
}