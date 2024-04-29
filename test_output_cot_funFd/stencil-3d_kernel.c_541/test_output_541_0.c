#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

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
  loopk:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 0; i < 40; i++) {
        i_col = i - 1;
        if (i == 0) {
          i_col = 39;
        }
        j_col = j - 1;
        if (j == 0) {
          j_col = 39;
        }
        k_col = k - 1;
        if (k == 0) {
          k_col = 39;
        }
        bound = (k_col * 40 + j_col) * 40 + i_col;
        t = orig[bound] + ((+1.0 * (orig[k_col * 40 + j_col] + orig[k * 40 + j_col] + orig[k * 40 + j] + orig[k * 40 + i] + orig[k_col * 40 + i] + orig[j_col * 40 + i] + orig[i_col * 40 + j] + orig[i_col * 40 + k] + orig[i_col * 40 + j_col])) / 10.0);
        sol[bound] = t;
      }
    }
  }
}