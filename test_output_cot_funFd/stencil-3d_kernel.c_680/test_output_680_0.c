#pragma ACCEL kernel

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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_i:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 40; j++) {
      loop_k:
      for (k = 0; k < 40; k++) {
        i_col = i - 1;
        if (i_col < 0) {
          i_col = 0;
        }
        j_col = j - 1;
        if (j_col < 0) {
          j_col = 0;
        }
        k_col = k - 1;
        if (k_col < 0) {
          k_col = 0;
        }
        bound = (i_col * (40 + 2 * 1) + (j_col)) * (40 + 2 * 1) + k_col;
        t = orig[bound] + orig[bound + 1] + orig[bound + 40] + orig[bound + 41] + 
          orig[bound + 160] + orig[bound + 161] + orig[bound + 176] + 
          orig[bound + 177] + orig[bound + 256] + orig[bound + 257] + 
          orig[bound + 272] + orig[bound + 273] + orig[bound + 320] + 
          orig[bound + 321] + orig[bound + 336] + orig[bound + 337] + 11;
        sol[bound] = t;
      }
    }
  }
}