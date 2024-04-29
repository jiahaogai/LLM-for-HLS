Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long k_pad;
  long j_pad;
  long i_pad;
  long idx;
  long idx_col;
  long idx_row;
  long idx_pad;
  long range_pad;
  long range_row;
  long range_col;
  long count;
  long count_col;
  long count_row;
  long count_pad;
  long val;
  long matrix[4];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_pad:
/* Standardize from: for(j_pad = 0;j_pad < 4;j_pad ++) {...} */
  for (j_pad = 0; j_pad <= 3; j_pad++) {
    long _in_j_pad = 0 + 4L * j_pad;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_pad:
/* Standardize from: for(k_pad = 0;k_pad < 4;k_pad ++) {...} */
    for (k_pad = 0; k_pad <= 3; k_pad++) {
      long _in_k_pad = 0 + 4L * k_pad;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
      for (i = 0; i < 32; i++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopj:
        for (j = 0; j < 32; j++) {
          long _in_j = _in_j_pad + j;
          
#pragma ACCEL PIPELINE auto{flatten}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loopk:
          for (k = 0; k < 32; k++) {
            long _in_k = _in_k_pad + k;
            idx = i * 32 * 32 + j * 32 + k;
            idx_col = k * 32 * 32 + j * 32 + i;
            idx_row = j * 32 * 32 + k * 32 + i;
            idx_pad = k_pad * 4 * 32 * 32 + j_pad * 4 * 32 + i_pad * 4 + k_col * 32 + j_col;
            count = 0;
            val = 0L;
            loopk_col:
            for (k_col = 0; k_col < 4; k_col++) {
               loopj_col:
               for (j_col = 0; j_col < 4; j_col++) {
                 i_col = i + k_col - 1;
                 if (((int )i_col) >= 0 && ((int )i_col) < 32) {
                   j_col = j + j_col - 1;
                   if (((int )j_col) >= 0 && ((int )j_col) < 32) {
                     val += orig[i_col * 32 + j_col] * matrix[count];
                     count++;
                   }
                 }
               }
            }
            sol[idx] = val;
          }
        }
      }
    }
  }
}
Error: