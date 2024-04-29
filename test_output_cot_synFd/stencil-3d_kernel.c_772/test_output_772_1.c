#pragma ACCEL kernel

// Designate the following function for hardware acceleration.

#pragma ACCEL PIPELINE auto{off}

// Do not automatically pipeline this loop.

#pragma ACCEL TILE FACTOR=auto{8}

// Keep this loop whole, without dividing it into smaller parts, and set the tile factor to 8.

#pragma ACCEL PIPELINE auto{}

// Automatically pipeline this loop.

#pragma ACCEL TILE FACTOR=auto{1}

// Keep this loop whole, without dividing it into smaller parts, and set the tile factor to 1.

#pragma ACCEL PARALLEL FACTOR=auto{3}

// Execute loop iterations sequentially, not concurrently, and set the parallel factor to 3.

#include <math.h>
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
      for (long ko = 0; ko <= 31; ko++) {
        long _in_ko = 1L + 1L * ko;
        sum0 = orig[_in_ko + (0) + (34) * (j + (34) * i)];
        sum1 = orig[_in_ko + (0) + (34) * (j + (34) * (i + (1)))] + orig[_in_ko + (0) + (34) * (j + (34) * (i - (1)))] + orig[_in_ko + (0) + (34) * (j + (1) + (34) * i)] + orig[_in_ko + (0) + (34) * (j - (1) + (34) * i)] + orig[_in_ko + (0) + (1) + (34) * (j + (34) * i)] + orig[_in_ko + (0) - (1) + (34) * (j + (34) * i)];
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[_in_ko + (0) + (34) * (j + (34) * i)] = mul0 + mul1;
      }
    }
  }
}