#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long x;
  long y;
  long z;
  long x1;
  long y1;
  long z1;
  long x2;
  long y2;
  long z2;
  long x3;
  long y3;
  long z3;
  long x4;
  long y4;
  long z4;
  long x5;
  long y5;
  long z5;
  long i_col;
  long j_col;
  long k_col;
  long i_row;
  long j_row;
  long k_row;
  long i_tmp;
  long j_tmp;
  long k_tmp;
  long t_col;
  long t_row;
  long t_tmp;
  long C0_idx;
  long C1_idx;
  long orig_idx;
  long sol_idx;
  C0_idx = 0;
  C1_idx = 1;
  i_col = 2;
  j_col = 2 * 390;
  k_col = 2 * 390 * 386;
  i_row = 1;
  j_row = 390;
  k_row = 390 * 386;
  t_col = 0;
  t = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_x1:
  for (x1 = 1; x1 < 390 - 1; x1++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y1:
    for (y1 = 1; y1 < 390 - 1; y1++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z1:
      for (z1 = 1; z1 < 386 - 1; z1++) {
        i_tmp = x1 * i_row;
        j_tmp = y1 * j_row;
        k_tmp = z1 * k_row;
        t_tmp = x1 + y1 * 390 + z1 * 390 * 386;
        loop_t:
        for (t = 0; t < 32768; t++) {
          orig_idx = i_tmp + j_tmp + k_tmp + t_tmp;
          sol[t] = ((C0 * orig[orig_idx - 2 - k_row]) + (C1 * orig[orig_idx - 1 - k_row]) + (C0 * orig[orig_idx + 1 - k_row]) + (C1 * orig[orig_idx + 2 - k_row]) + (C0 * orig[orig_idx - 2]) + (C1 * orig[orig_idx - 1]) + (C0 * orig[orig_idx + 1]) + (C1 * orig[orig_idx + 2]) + (C0 * orig[orig_idx - 2 + k_row]) + (C1 * orig[orig_idx - 1 + k_row]) + (C0 * orig[orig_idx + 1 + k_row]) + (C1 * orig[orig_idx + 2 + k_row])) / (C1 * 8);
        }
      }
    }
  }
  z1 = 386 - 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_x2:
  for (x2 = 390; x2 < 39304; x2++) {
    
#