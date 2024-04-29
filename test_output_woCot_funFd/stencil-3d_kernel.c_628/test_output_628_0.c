#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long delta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
    for (j = 1 + 2; j <= 32L + 2; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 1; i <= 32L + 1; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = ((orig[i_col + ((j_col + (k_col * 32L))) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 2L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 3L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 4L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 5L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 6L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 7L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 8L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 9L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 10L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 11L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 12L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 13L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 14L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 15L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 16L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 17L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 18L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 19L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 20L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 21L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 22L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 23L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 24L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 25L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 26L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 27L) * 39304];
        buf += ((orig[i_col + ((j_col + (k_col * 32L)) + 32L * 28L) * 39304] + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 29L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 30L) * 39304]) + orig[i_col + ((j_col + (k_col * 32L)) + 32L * 31L) * 39304];
        delta = ((buf + 32L) / 64L) - orig[i_col + j_col + k_col * 32L];
        sol[i_col + j_col + k_col * 32L] = delta;
      }
    }
  }
}