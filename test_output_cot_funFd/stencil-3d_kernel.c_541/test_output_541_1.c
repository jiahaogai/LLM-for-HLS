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
  long num_pad;
  long num_orig;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long k_pad;
  long j_pad;
  long i_pad;
  long k_idx;
  long j_idx;
  long i_idx;
  long k_up;
  long k_down;
  long j_up;
  long j_down;
  long i_up;
  long i_down;
  long sum;
  NX = 32;
  NY = 32;
  NZ = 32;
  P = 1;
  Q = 1;
  R = 1;
  pad_sz = 1;
  half_sz = pad_sz + P;
  num_pad = pad_sz + NX;
  num_orig = NX - 2 * P;
  k_col = NZ + 2 * pad_sz;
  j_col = NY + 2 * pad_sz;
  i_col = NX + 2 * pad_sz;
  k_row = 1 + 2 * q;
  j_row = 1 + 2 * p;
  i_row = 1 + 2 * r;
  k_pad = pad_sz - q;
  j_pad = pad_sz - p;
  i_pad = pad_sz - r;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
  for (k = 0; k < k_col; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < j_col; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 0; i < i_col; i++) {
        k_idx = k - pad_sz + q;
        j_idx = j - pad_sz + p;
        i_idx = i - pad_sz + r;
        sum = 0.0;
        loop_k_up:
        for (k_up = -pad_sz; k_up < 0; k_up++) {
          loop_j_up:
          for (j_up = -pad_sz; j_up < 0; j_up++) {
            loop_i_up:
            for (i_up = -pad_sz; i_up < 0; i_up++) {
              idx = i_idx + i_up * i_row;
              if (idx >= 0 && idx < NX) {
                jdx = j_idx + j_up * j_row;
                if (jdx >= 0 && jdx < NY) {
                  kdx = k_idx + k_up * k_row;
                  if (kdx >= 0 && kdx < NZ) {
                    sum += orig[kdx * j_row * i_row + jdx * i_row + idx] * 4.0;
                  }
                }
              }
            }
          }
        }
        loop_k_down:
        for (k_down = 1; k_down <= 1 + pad_sz; k_down++) {
          loop_j_down:
          for (j_down = 1; j_down <= 1 + pad_sz; j_down++) {