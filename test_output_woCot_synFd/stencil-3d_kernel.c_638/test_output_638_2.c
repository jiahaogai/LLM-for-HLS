#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_;
  long _out_;
  _in_ = 0L;
  _out_ = 39304L;
  idx = _in_;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_x:
  for (i = 0L; i < 40L; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
    for (j = 0L; j < 40L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z:
      for (k = 0L; k < 40L; k++) {
        sol[idx] = ((2 * orig[idx]) + (C0 * (orig[idx + _in_] + orig[idx + _out_]))) / (C1 + 2.0);
        ++idx;
      }
      idx += 160L;
    }
    idx += 160L;
  }
}