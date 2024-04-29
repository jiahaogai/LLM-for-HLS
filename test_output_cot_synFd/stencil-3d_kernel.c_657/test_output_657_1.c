#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long P;
  long Q;
  long R;
  long M;
  long pad_sz;
  long pad_idx;
  long pad_end;
  long bp;
  long one;
  long x;
  long y;
  long z;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  NX = 32;
  NY = 32;
  NZ = 32;
  P = 1;
  Q = 1;
  R = 1;
  M = NX - 2 * P;
  pad_sz = P;
  pad_idx = 0 + pad_sz;
  pad_end = NX - 1 + pad_sz;
  bp = pad_sz << 1;
  one = 1L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_x:
  for (x = 0 + pad_sz; x < 32 + pad_sz; x++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
    for (y = 0 + pad_sz; y < 32 + pad_sz; y++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z:
      for (z = 0 + pad_sz; z < 32 + pad_sz; z++) {
        idx = ((x - pad_idx) + (y - pad_idx) * (NX + 2 * pad_sz) + (z - pad_idx) * (NX + 2 * pad_sz) * (NY + 2 * pad_sz)) >> 1;
        sol[idx] = ((C0 * (orig[idx] + orig[idx + bp])) + (C1 * (orig[idx + 1] + orig[idx + 1 + bp]))) / (one + (2L * C1));
      }
    }
  }
}