**TODO:**
 -#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long bound;
  long bound_col;
  long r;
  long q;
  long p;
  long r_col;
  long q_col;
  long p_col;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  bound = 4 + 0 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound_col = 4 + 0 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 4 + 0 + 1; i < 39304 + 4 + 0 + 1 - 3; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 4 + 0 + 1; j < 39304 + 4 + 0 + 1 - 3; j++) {
      for (k = 4 + 0 + 1; k < 39304 + 4 + 0 + 1 - 3; k++) {
        i_col = i + (-4);
        j_col = j + (-4);
        k_col = k + (-4);
        val = orig[i_col * 39304 + j_col * 4 + k_col];
        r = val;
        q_col = k_col + 1;
        q = val;
        p_col = k_col - 1;
        p = val;
        k_col = k_col + 4;
        q = q + orig[i_col * 39304 + j_col * 4 + k_col];
        p = p + orig[i_col * 39304 + j_col * 4 + p_col];
        k_col = k_col + 4;
        q = q + orig[i_col * 39304 + j_col * 4 + k_col];
        p = p + orig[i_col * 39304 + j_col * 4 + p_col];
        k_col = k_col + 4;
        q = q + orig[i_col * 39304 + j_col * 4 + k_col];
        p = p + orig[i_col * 39304 + j_col * 4 + p_col];
        k_col = k_col + 1;
        q = q + val;
        p = p + orig[i_col * 39304 + j_col * 4 + k_col];
        sol[i * 32768 + j] = ((p + q) / 8192);
      }
    }
  }
}