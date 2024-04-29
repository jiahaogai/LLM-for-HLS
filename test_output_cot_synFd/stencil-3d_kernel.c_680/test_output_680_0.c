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
  long tmp;
  long tmp_row;
  long tmp_col;
  long tmp_slice;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
  for (i = 0L; i <= 39L - 1L; i += 40L) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j <= 39L - 1L; j += 40L) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
      for (k = 0L; k <= 39L - 1L; k += 1L) {
        k_col = ((40L * k) + j);
        j_col = ((40L * i) + j);
        i_col = ((40L * i) + k);
        buf = orig[i_col] + orig[j_col] + orig[k_col];
        tmp_slice = buf;
        loop_tmp_col:
        for (tmp_col = 0L; tmp_col <= 39L - 1L; tmp_col += 1L) {
          tmp_row = tmp_slice;
          tmp_slice = orig[tmp_col + k_col] + tmp_row;
        }
        tmp = tmp_slice;
        sol[i_col] = tmp;
      }
    }
  }
}