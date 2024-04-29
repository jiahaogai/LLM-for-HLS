#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 2; k < 39302 - 2; k++) {...} */
  for (k = 2 + 2984; k < 39302 + 2 - 2984; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 39300 - 2; j++) {...} */
    for (j = 2 + 2; j < 39300 + 2 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 39300 - 2; i++) {...} */
      for (i = 2 + 2; i < 39300 + 2 - 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        tmp = 0;
        loop_buf:
/* Standardize from: for(int idx = 0; idx < 256; ++idx) {...} */
        for (long idx = 0; idx < 256; ++idx) {
          tmp += orig[idx + k_col * 39300 + j_col * 39300 + i_col] * buf[idx];
        }
        sol[k * 39300 + j * 39300 + i] = tmp;
      }
    }
  }
}