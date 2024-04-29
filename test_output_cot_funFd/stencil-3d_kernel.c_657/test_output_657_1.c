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
  long pad_sz;
  long half_sz;
  long nidx;
  long idx_in;
  long idx_out;
  long v;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  initialize:
  for (v = 0; v < 39304; v++) {
    orig[v] = v;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  pad_sz = 1;
  NX = 64;
  NY = 64;
  NZ = 64;
  P = NX + 2 * pad_sz;
  Q = NY + 2 * pad_sz;
  R = NZ + 2 * pad_sz;
  half_sz = pad_sz + 1;
  nidx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_x:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_y:
    for (j = 0; j < 64; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_z:
      for (k = 0; k < 64; k++) {
        idx_in = ((pad_sz + i) * Q + pad_sz + j) * R + pad_sz + k;
        idx_out = nidx;
        sol[idx_out] = ((C0 * orig[idx_in]) + (C1 * (orig[idx_in + 1] + orig[idx_in - 1] + orig[idx_in + P] + orig[idx_in - P] + orig[idx_in + Q] + orig[idx_in - Q] + orig[idx_in + R] + orig[idx_in - R])));
        nidx++;
      }
    }
  }
}