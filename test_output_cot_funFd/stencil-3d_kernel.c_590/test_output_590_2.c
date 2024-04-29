#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_;
  long _out_;
  long _tmp_;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_x:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
  for (i = 1 + 32L; i-- > 1 + 0L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 32L; j-- > 1 + 0L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
      for (k = 1 + 32L; k-- > 1 + 0L; ) {
        _in_ = 0L;
        _out_ = 0L;
        loop_k:
        for (idx = -1L; idx > -33L; idx--) {
          _tmp_ = orig[idx + 0L + ((32L + 1L + 0L) * (32L + 1L + 0L) * i)] + orig[idx + 1L + ((32L + 1L + 0L) * (32L + 1L + 0L) * i)] + orig[idx + 0L + ((32L + 1L + 0L) * (32L + 1L + 0L) * (j + 1L)) + 32L * 32L] + orig[idx + 1L + ((32L + 1L + 0L) * (32L + 1L + 0L) * (j + 1L)) + 32L * 32L] + orig[idx + 0L + ((32L + 1L + 0L) * (32L + 1L + 0L) * (k + 1L)) + 32L * (32L + 1L)] + orig[idx + 1L + ((32L + 1L + 0L) * (32L + 1L + 0L) * (k + 1L)) + 32L * (32L + 1L)] + orig[idx + ((32L + 1L + 0L) * (32L + 1L + 0L) * (k + 1L)) + 32L * (32L + 1L)];
          if (idx == -1L) {
            _out_ = _tmp_;
          }
          else {
            _in_ = _tmp_;
          }
        }
        sol[i + (32L + 1L) * ((j + (32L + 1L) * (k)))) = ((-1L) * _in_) + _out_;
      }
    }
  }
}