#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_in;
  long idx_out;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i > 32 + 1; i--) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_in = idx_col + idx_row * 32;
        idx_out = idx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig[idx_in + 1] + orig[idx_in - 1] + orig[idx_in + 32] + orig[idx_in - 32] + orig[idx_in + 32 * 32] + orig[idx_in - 32 * 32]))) / (C0 + C1);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_1:
/* Standardize from: for(j = 32 + 1 - 2; j < 32 + 1; j++) {...} */
    for (j = 32 + 1 - 2; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_1:
/* Standardize from: for(i = 32 + 1 - 3; i < 32 + 1; i++) {...} */
      for (i = 32 + 1 - 3; i < 32 + 1; i++) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_in = idx_col + idx_row * 32;
        idx_out = idx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig[idx_in + 1] + orig[idx_in - 1] + orig[idx_in + 32] + orig[idx_in - 32] + orig[idx_in + 32 * 32] + orig[idx_in - 32 * 32]))) / (C0 + C1);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_2:
/* Standardize from: for(j = 32 + 1; j < 32 + 1 + 2; j++) {...} */
    for (j = 32 + 1; j < 32 + 1 + 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_2:
/* Standardize from: for(i = 32 + 1; i < 32 + 1 + 3; i++) {...} */
      for (i = 32 + 1; i < 32 + 1 + 3; i++) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_in = idx_col + idx_row * 32;
        idx_out = idx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig[idx_in + 1] + orig[idx_in - 1] + orig[idx_in + 32] + orig[idx_in - 32] + orig[idx_in + 32 * 32] + orig[idx_in - 32 * 32]))) / (C0 + C1);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k_1:
/* Standardize from: for(k = 32 + 1 - 1; k < 32 + 1; k++) {...} */
  for (k = 32 + 1 - 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_3:
/* Standardize from: for(j = 0; j < 32 + 1; j++) {...} */
    for (j = 0; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i_3:
/* Standardize from: for(i = 0; i < 32 + 1; i++) {...} */
      for (i = 0; i < 32 + 1; i++) {
        idx = i + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_col = i - 1 + (j - 1) * 32 + (k - 1) * 32 * 32;
        idx_row = i + (j - 1) * 32 + (k - 1) * 32 * 32 - 32 * 32;
        idx_in = idx_col + idx_row * 32;
        idx_out = idx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig