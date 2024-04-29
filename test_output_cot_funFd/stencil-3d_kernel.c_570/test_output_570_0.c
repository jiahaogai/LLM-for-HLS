#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1 + 16L;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
     for (j = 1 + 32L; j > 32L; j--) {
        j_col = j - 1 + 16L;
        loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
        for (i = 1 + 32L; i > 16L; i--) {
          i_col = i - 1 + 16L;
          buf[0] = orig[i_col + 32L + 0L + ((j_col + 32L) * 32L) + ((k_col + 32L) * 32L * 32L)];
          buf[1] = orig[i_col + 0L + ((j_col + 32L) * 32L) + ((k_col + 32L) * 32L * 32L)];
          buf[2] = orig[i_col + 32L + 0L + (j_col * 32L) + (k_col * 32L * 32L)];
          buf[3] = orig[i_col + 0L + (j_col * 32L) + (k_col * 32L * 32L)];
          buf[4] = orig[i_col + 32L + 16L + ((j_col + 16L) * 32L) + ((k_col + 32L) * 32L * 32L)];
          buf[5] = orig[i_col + 16L + ((j_col + 16L) * 32L) + ((k_col + 32L) * 32L * 32L)];
          buf[6] = orig[i_col + 32L + 16L + (j_col * 32L) + (k_col * 32L * 32L)];
          buf[7] = orig[i_col + 16L + (j_col * 32L) + (k_col * 32L * 32L)];
          sol[i_col + 32L + ((j_col + 32L) * 32L) + ((k_col + 32L) * 32L * 32L)] = ((buf[0] + buf[1]) + buf[2]) + buf[3];
          sol[i_col + 0L + ((j_col + 32L) * 32L) + ((k_col + 32L) * 32L * 32L)] = (((buf[1] * 2L) + buf[2]) + buf[3]) + buf[4];
          sol[i_col + 32L + 0L + (j_col * 32L) + (k_col * 32L * 32L)] = (((buf[1] + buf[2]) * 2L) + buf[3]) + buf[5];
          sol[i_col + 0L + (j_col * 32L) + (k_col * 32L * 32L)] = (((buf[1] * 4L) + (buf[2] * 2L)) + buf[3]) + buf[6];
          sol[i_col + 32L + 16L + ((j_col + 16L) * 32L) + ((k_col + 16L) * 32L * 32L)] = ((buf[2] + buf[3]) + buf[4]) + buf[5];
          sol[i_col + 16L + ((j_col + 16L) * 32L) + ((k_col + 16L) * 32L * 32L)] = (((buf[2] * 2L) + buf[3]) + buf[4]) + buf[6];
          sol[i_col + 32L + 16L + (j_col * 32L) + (k_col * 32L * 32L)] = (((buf[2] + buf[3]) * 2L) + buf[4]) + buf[7];
          sol[i_col + 16L + (j_col * 32L) + (k_col * 32L * 32L)] = (((buf[2] * 4L) + (buf[3] * 2L)) + buf[4]) + buf[7];
        }
      }
  }
}