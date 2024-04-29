#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{30}

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
  s = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 16L; i--) {
        buf = ((orig[i + 32L * (j + 32L * k)] + orig[i + 1L + 32L * (j + 32L * k)] + orig[i - 1L + 32L * (j + 32L * k)] + orig[i + 32L * (j + 1L + 32L * k)] + orig[i + 32L * (j - 1L + 32L * k)] + orig[i + 32L * (j + 32L * (k + 1L))]) + (orig[i + 32L * (j - 32L * k)] + orig[i + 1L + 32L * (j - 32L * k)] + orig[i - 1L + 32L * (j - 32L * k)] + orig[i + 32L * (j + 1L - 32L * k)] + orig[i + 32L * (j - 1L - 32L * k)] + orig[i + 32L * (j + 32L * (k - 1L))])) / 6L;
        sol[i + 32L * (j + 32L * k)] = buf;
      }
    }
  }
}