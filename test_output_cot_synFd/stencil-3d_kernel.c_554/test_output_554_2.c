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
  long s;
  long t;
  long u;
  long pass;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_x:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_y:
    for (j = 0; j < 40; j++) {
      loop_z:
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
        s = orig[i_col + 40L * j_col + 40L * 40L * k_col];
        t = orig[i_col + 40L * (j_col + 1L) + 40L * 40L * k_col];
        u = orig[i_col + 40L * (j_col + 1L) + 40L * 40L * (k_col + 1L)];
        s = (4L * s) - (2L * t) - (2L * u) + orig[i_col + 40L * 40L * k_col] +
            orig[i_col + 40L * 40L * (k_col + 1L)] +
            orig[i_col + 40L * j_col + 40L * 40L * (k_col + 1L)] +
            orig[i_col + 40L * (j_col + 1L) + 40L * 40L * (k_col + 1L)];
        t = (4L * t) - (2L * s) - (2L * u) + orig[i_col + 40L * k_col] +
            orig[i_col + 40L * (k_col + 1L)] +
            orig[i_col + 40L * j_col + 40L * (k_col + 1L)] +
            orig[i_col + 40L * (j_col + 1L) + 40L * (k_col + 1L)];
        u = (4L * u) - (2L * s) - (2L * t) + orig[k_col] + orig[(k_col + 1L)] +
            orig[j_col + 40L * (k_col + 1L)] +
            orig[(j_col + 1L) + 40L * (k_col + 1L)];
        sol[i + 40L * j + 40L * 40L * k] = ((s + t) + u) / 8L;
      }
    }
  }
}