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
  _out_ = 0L;
  idx = 0L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_x:
  for (i = 1L; i < 32L + 1L; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
    for (j = 1L; j < 32L + 1L; j++) {
      loop_z:
      for (k = 1L; k < 32L + 1L; k++) {
        idx = ((i * 32L + j) * 32L + k) - 1L;
        sol[idx] = ((C0 * orig[idx - 1L - 32L - 32L]) + (C0 * orig[idx + 1L - 32L - 32L]) + (C0 * orig[idx - 32L - 1L]) + (C0 * orig[idx - 32L + 1L]) + (C0 * orig[idx + 32L - 1L]) + (C0 * orig[idx + 32L + 1L]) + (C1 * orig[idx]) + - (orig[idx])) / (C1 + 1L);
      }
    }
  }
}