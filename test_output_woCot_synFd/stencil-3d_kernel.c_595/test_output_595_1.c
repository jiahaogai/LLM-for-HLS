#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long kmin;
  long kmax;
  long jmin;
  long jmax;
  long imin;
  long imax;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  kmin = 1;
  kmax = 4;
  jmin = 1;
  jmax = 4;
  imin = 1;
  imax = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 32; i++) {
        idx = i + 32 * j + 32 * 32 * k;
        t1 = orig[idx + 0] + orig[idx + 32];
        t2 = orig[idx + 1] + orig[idx + 31];
        t3 = orig[idx + 32 * 32] + orig[idx + 31 * 32];
        sol[idx] = t1 + t2 + t3;
      }
    }
  }
}