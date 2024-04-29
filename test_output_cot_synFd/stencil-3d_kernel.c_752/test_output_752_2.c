#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long x;
  long y;
  long z;
  long t;
  long bound;
  x = 4;
  y = 4;
  z = 4;
  bound = 1 + 4 + 4 + 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_x:
  for (x = 1; x < 4 + 1; x++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_y:
    for (y = 1; y < 4 + 1; y++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loop_z:
      for (z = 1; z < 4 + 1; z++) {
        idx = x * (4 * (4 + 1) * (4 + 1)) + y * ((4 + 1) * (4 + 1)) + z * (4 + 1) + 1;
        t = C0 * (orig[idx - 1 - (4 + 1) * (4 + 1) * (4 + 1)] + orig[idx + 1 - (4 + 1) * (4 + 1) * (4 + 1)] + orig[idx - (4 + 1) * (4 + 1) - 1] + orig[idx - (4 + 1) * (4 + 1)] + orig[idx - (4 + 1) * (4 + 1) + 1] + orig[idx + (4 + 1) * (4 + 1) - 1] + orig[idx + (4 + 1) * (4 + 1)] + orig[idx + (4 + 1) * (4 + 1) + 1] - 8 * orig[idx]) / 8 + C1 * orig[idx];
        sol[idx] = t;
      }
    }
  }
}