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
  long bound_in;
  long r;
  long b;
  long r_col;
  long b_col;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        b = ((k_col * (32L + 1L) + j_col) * (32L + 1L) + i_col) * 2L;
        r = (k_col * (32L + 1L) + j_col) * (32L + 1L) + i_col;
        bound = 32L + 1L - i;
        bound_in = 32L + 1L - j;
        loop_r:
        for (r_col = r; r_col < r + bound; r_col++) {
          b_col = b + bound_in;
          tmp = 0L;
          loop_b:
          for (b_col = b_col; b_col < b_col + bound; b_col++) {
            tmp += orig[b_col] * sol[r_col];
          }
          sol[b_col] = tmp;
        }
      }
    }
  }
}