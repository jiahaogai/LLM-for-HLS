#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{8}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_;
  long _out_;
  long _tmp_[8][8][8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 8; k++) {...} */
  for (k = 0L; k < 8L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 8; j++) {...} */
    for (j = 0L; j < 8L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
      for (i = 0L; i < 8L; i++) {
        _in_ = ((8L * 8L) * k) + (8L * j) + i;
        _out_ = 0L;
        loop_idx:
/* Standardize from: for(idx = 0; idx < 8; idx++) {...} */
        for (idx = 0L; idx < 8L; idx++) {
          _tmp_[idx][j][i] = orig[_in_ + idx];
          _out_ += _tmp_[idx][j][i];
        }
        sol[_out_] = _out_;
      }
    }
  }
}