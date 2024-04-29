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
  _out_ = 32768L;
  idx = 0L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_j:
  for (j = 1L; j < 32L; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_k:
    for (k = 1L; k < 32L; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1L; i < 32L; i++) {
        idx = ((32L * (32L * k)) + (32L * j)) + i;
        sol[idx] = ((C0 * orig[idx]) + (C1 * ((((32L * (k - 1L)) + (j - 1L)) + i) - 1L < 0 ? 0 : ((32L * (k - 1L)) + (j - 1L)) + i))) + _out_;
      }
    }
  }
}