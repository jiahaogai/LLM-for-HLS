#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long mult;
  long _in_[39304];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      i_col = i * 40;
      for (k = 0; k < 40; k++) {
        k_col = k * 40;
        idx = i_col + k;
        idx_col = k_col + j;
        mult = orig[idx] * C0;
        mult += orig[idx_col] * C1;
        _in_[idx] = mult;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (k = 0; k < 40; k++) {
      k_col = k * 40;
      idx = k_col + j;
      sol[idx] = _in_[idx];
    }
  }
}