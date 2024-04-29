#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 16L; k <= 31L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 16L; j <= 31L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 16L; i <= 31L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = ((orig[i + (j + (k * 40L)) * 40L] + orig[i_col + (j + (k * 40L)) * 40L] + orig[i + (j_col + (k * 40L)) * 40L] + orig[i_col + (j_col + (k * 40L)) * 40L]) - (orig[i + (j + (k_col * 40L)) * 40L] + orig[i_col + (j + (k_col * 40L)) * 40L] + orig[i + (j_col + (k_col * 40L)) * 40L] + orig[i_col + (j_col + (k_col * 40L)) * 40L])) / (4 * 40L * 40L);
        sol[i + (j + (k * 40L)) * 40L] = buf;
      }
    }
  }
}