#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long orig_idx;
  long sol_idx;
  long C0_idx;
  long C1_idx;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 40; j++) {
      loop_k_col:
      for (k_col = 0; k_col < 8; k_col++) {
        loop_i_col:
        for (i_col = 0; i_col < 40; i_col++) {
          loop_j_col:
          for (j_col = 0; j_col < 8; j_col++) {
            C0_idx = ((40 * (4 - 1)) + i) * (40 * (8 - 1)) + ((40 * (8 - 1)) + j_col);
            C1_idx = ((40 * (1 - 1)) + i_col) * (40 * (8 - 1)) + ((40 * (8 - 1)) + j_col);
            orig_idx = i * 40 + i_col;
            sol_idx = C0_idx;
            orig[orig_idx] += +C0 * sol[sol_idx];
            sol_idx = C1_idx;
            orig[orig_idx] += +C1 * sol[sol_idx];
          }
        }
      }
    }
  }
//#pragma endscop
}