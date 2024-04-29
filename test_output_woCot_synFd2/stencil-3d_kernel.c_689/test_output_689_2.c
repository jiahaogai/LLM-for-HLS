#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 2; k < 32 + 2; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 2; j < 32 + 2; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 2; i < 32 + 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        idx = i_col + (j_col + (k_col << 5)) << 3;
        C0_idx = k_col << 6;
        C1_idx = j_col << 6;
        sol[idx] = C0 * (orig[idx] + ((C1_idx + 1) < 30 ? orig[idx + 1] : 0) + ((C1_idx + 2) < 30 ? orig[idx + 2] : 0) + ((C1_idx + 3) < 30 ? orig[idx + 3] : 0) + ((C1_idx + 4) < 30 ? orig[idx + 4] : 0) + ((C1_idx + 5) < 30 ? orig[idx + 5] : 0) + ((C1_idx + 6) < 30 ? orig[idx + 6] : 0) + ((C1_idx + 7) < 30 ? orig[idx + 7] : 0)) + ((C0_idx + 1) < 30 ? (orig[idx + 30] + ((C1_idx + 1 + 8) < 38 ? orig[idx + 30 + 8] : 0) + ((C1_idx + 1 + 16) < 38 ? orig[idx + 30 + 16] : 0) + ((C1_idx + 1 + 24) < 38 ? orig[idx + 30 + 24] : 0)) : 0);
      }
    }
  }
}