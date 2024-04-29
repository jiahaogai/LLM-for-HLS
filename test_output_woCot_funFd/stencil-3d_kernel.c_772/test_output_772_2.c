The HLS tool translates this function into the following HLS code.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (long i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (long j = 1; j < 33; j++) {
      for (long k = 1; k < 33; k++) {
        long _in_ko = 1L + 1L * (32L * (32L * k + j) + i);
        sum0 = orig[_in_ko];
        sum1 = orig[_in_ko + 1] + orig[_in_ko - 1] + orig[_in_ko + 32] + orig[_in_ko - 32] + orig[_in_ko + 32 * 32] + orig[_in_ko - 32 * 32] + orig[_in_ko + 1 + 32 * 32] + orig[_in_ko - 1 + 32 * 32] + orig[_in_ko + 32 + 32 * 32] + orig[_in_ko - 32 + 32 * 32];
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[_in_ko] = mul0 + mul1;
      }
    }
  }
}