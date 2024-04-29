#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[25][25][25];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 25; k++) {...} */
  for (k = 0L; k <= 24L; k++) {
    long k_col_tmp = k - 1;
    long k_col = (k_col_tmp < 0 ? 0 : k_col_tmp);
    long k_row_tmp = k + 1;
    long k_row = (k_row_tmp > 24 ? 24 : k_row_tmp);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 0; j < 25; j++) {...} */
    for (j = 0L; j <= 24L; j++) {
      long j_col_tmp = j - 1;
      long j_col = (j_col_tmp < 0 ? 0 : j_col_tmp);
      long j_row_tmp = j + 1;
      long j_row = (j_row_tmp > 24 ? 24 : j_row_tmp);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 0; i < 25; i++) {...} */
      for (i = 0L; i <= 24L; i++) {
        long i_col_tmp = i - 1;
        long i_col = (i_col_tmp < 0 ? 0 : i_col_tmp);
        long i_row_tmp = i + 1;
        long i_row = (i_row_tmp > 24 ? 24 : i_row_tmp);
        long idx = i + j * 25 + k * 25 * 25;
        long sum = 0L;
        loop_k_col:
/* Standardize from: for(k_col = (i - 1); k_col <= (i + 1); k_col++) {...} */
        for (k_col = ((i_col < 0) ? 0 : i_col); k_col <= ((i_col + 1) > 24 ? 24 : (i_col + 1)); k_col++) {
          loop_j_col:
/* Standardize from: for(j_col = (j - 1); j_col <= (j + 1); j_col++) {...} */
          for (j_col = ((j_col < 0) ? 0 : j_col); j_col <= ((j_col + 1) > 24 ? 24 : (j_col + 1)); j_col++) {
            loop_i_col:
/* Standardize from: for(i_col = (k - 1); i_col <= (k + 1); i_col++) {...} */
            for (i_col = ((k_col < 0) ? 0 : k_col); i_col <= ((k_col + 1) > 24 ? 24 : (k_col + 1)); i_col++) {
              sum += orig[i_col + j_col * 25 + k_col * 25 * 25] ;
            }
          }
        }
        buf[k][j][i] = sum;
      }
    }
    loop_k_row:
/* Standardize from: for(k_row = (k + 1