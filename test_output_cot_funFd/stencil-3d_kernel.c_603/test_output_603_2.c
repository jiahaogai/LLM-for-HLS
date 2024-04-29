Expected: 
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
  long nx;
  long ny;
  long nz;
  long q_pad;
  long r_pad;
  long nx_pad;
  long ny_pad;
  long nz_pad;
  long idx_pad;
  long idx_n;
  long c0;
  long c1;
  long c2;
  long v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  pad_sz = 1;
  half_sz = 3 - 2 * pad_sz;
  NX = 33;
  NY = 34;
  NZ = 35;
  P = pad_sz;
  Q = pad_sz;
  R = pad_sz;
  nx = NX - 2 * P;
  ny = NY - 2 * Q;
  nz = NZ - 2 * R;
  nx_pad = NX + 2 * pad_sz;
  ny_pad = NY + 2 * pad_sz;
  nz_pad = NZ + 2 * pad_sz;
  q_pad = Q + pad_sz;
  r_pad = R + pad_sz;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 32768; i++) {
    sol[i] = ((long )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 39304; i++) {
    orig[i] = 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 34; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 35; k++) {
        idx = i * ny * nz + j * nz + k;
        idx_pad = i * ny_pad * nz_pad + j * nz_pad + k;
        c0 = 0.0;
        c1 = 0.0;
        c2 = 0.0;
        v = orig[idx_pad - nz_pad - 1] + orig[idx_pad - nz_pad] + orig[idx_pad - nz_pad + 1] + orig[idx_pad - 1] + orig[idx_pad + 1] + orig[idx_pad + nz_pad - 1] + orig[idx_pad + nz_pad] + orig[idx_pad + nz_pad + 1];
        for (c2 = 0.0; c2 < 25.0; c2 += 1.0) {
          for (c1 = 0.0; c1 < 25.0; c1 += 1.0) {
            for (c0 = 0.0; c0 < 25.0; c0 += 1.0) {
              idx_n = idx + ((int )