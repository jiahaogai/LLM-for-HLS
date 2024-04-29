#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long start;
  long end;
  long step;
  long t;
  long pad_size;
  pad_size = 1;
  start = 1 - pad_size;
  end = 32 + pad_size;
  step = 1;
  idx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
  for (j = 0; j < 32 + 2 * pad_size; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 0; k < 32 + 2 * pad_size; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
      for (i = 0; i < 32 + 2 * pad_size; i++) {
        t = ((C0 * (orig[idx + 32 * 32 * -1] + orig[idx + 32 * 32 * 1])) + (C1 * (orig[idx + 32 * -1] + orig[idx + 32 * 1] + orig[idx + 32 * 32] + orig[idx + 32 * 32 * 32]))) / ((C0 + C1) * 2);
        sol[idx] = t;
        ++idx;
      }
    }
  }
}