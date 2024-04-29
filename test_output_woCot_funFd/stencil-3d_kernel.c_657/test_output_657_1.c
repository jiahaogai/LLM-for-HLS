#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i + ((32 + 1) * (j - 1));
        k_col = k + ((32 + 1) * (32 + 1)) * (j - 1);
        idx = i_col + (32 + 1) * k_col;
        tmp = ((C0 * orig[idx]) + (C1 * (orig[idx + 1] + orig[idx + 32 + 1] + orig[idx + (32 + 1) * 2] + orig[idx + (32 + 1) * 3] + orig[idx + (32 + 1) * 4] + orig[idx + (32 + 1) * 5] + orig[idx + (32 + 1) * 6] + orig[idx + (32 + 1) * 7] + orig[idx + (32 + 1) * 8] + orig[idx + (32 + 1) * 9] + orig[idx + (32 + 1) * 10] + orig[idx + (32 + 1) * 11] + orig[idx + (32 + 1) * 12] + orig[idx + (32 + 1) * 13] + orig[idx + (32 + 1) * 14] + orig[idx + (32 + 1) * 15] + orig[idx + (32 + 1) * 16] + orig[idx + (32 + 1) * 17] + orig[idx + (32 + 1) * 18] + orig[idx + (32 + 1) * 19] + orig[idx + (32 + 1) * 20] + orig[idx + (32 + 1) * 21] + orig[idx + (32 + 1) * 22] + orig[idx + (32 + 1) * 23] + orig[idx + (32 + 1) * 24] + orig[idx + (32 + 1) * 25] + orig[idx + (32 + 1) * 26] + orig[idx + (32 + 1) * 27] + orig[idx + (32 + 1) * 28] + orig[idx + (32 + 1) * 29] + orig[idx + (32 + 1) * 30] + orig[idx + (32 + 1) * 31]))) >> (32);
        sol[idx] = tmp;
      }
    }
  }
}