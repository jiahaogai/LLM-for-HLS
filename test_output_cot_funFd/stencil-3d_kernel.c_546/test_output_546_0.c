#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        idx = i + (j - 1) * (32 + 0) + (k - 1) * (32 + 0) * (32 + 1);
        s = C0 * (orig[idx - 1 - (32 + 0) * (32 + 1)] + orig[idx + 1 - (32 + 0) * (32 + 1)]);
        s += C0 * (orig[idx - (32 + 0) * (32 + 1)] + orig[idx + (32 + 0) * (32 + 1)]);
        s += C1 * (orig[idx - 1 - 0] + orig[idx + 1 - 0] + orig[idx - 1 + 0] + orig[idx + 1 + 0]);
        s = orig[idx] - s / 4.0;
        sol[idx] = s;
      }
    }
  }
}