#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idxP;
  long idxM;
  long k_start;
  long k_end;
  long j_start;
  long j_end;
  long i_start;
  long i_end;
  long range;
  long ref;
  long k_step;
  long j_step;
  long i_step;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  k_start = 1 + -3;
  k_end = 32 + 1 - 1;
  k_step = 1;
  if (k_start < 0) {
    k_start = 0;
  }
  if (k_end < 0) {
    k_end = 0;
  }
  if (k_step < 0) {
    range = 0 - k_start;
    k_step = 0 - k_step;
  }
  else {
    range = k_end - k_start;
  }
  range = (range + k_step - 1) / k_step;
  assert(range > 0);
  for (k = k_start, idx = 393216, k_col = 39304; k < k_end; k += k_step, idx += 8, k_col -= 1) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    j_start = 1 + -3;
    j_end = 32 + 1 - 1;
    j_step = 1;
    if (j_start < 0) {
      j_start = 0;
    }
    if (j_end < 0) {
      j_end = 0;
    }
    if (j_step < 0) {
      range = 0 - j_start;
      j_step = 0 - j_step;
    }
    else {
      range = j_end - j_start;
    }
    range = (range + j_step - 1) / j_step;
    assert(range > 0);
    for (j = j_start, idxP = idx + 1, idxM = idx - 1, j_col = 39304 - 1; j < j_end; j += j_step, idxP += 8, idxM -= 8, j_col -= 1) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      i_start = 1 + -3;
      i_end = 32 + 1 - 1;
      i_step = 1;
      if (i_start < 0) {
        i_start = 0;
      }
      if (i_end < 0) {
        i_end = 0;
      }
      if (i_step < 0) {
        range = 0 - i_start;
        i_step = 0 - i_step;
      }
      else {
        range = i_end - i_start;
      }