#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_k:
  for (k = 1; k < 32 + 1 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 1; j < 32 + 1 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_i:
      for (i = 1; i < 32 + 1 - 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = (C0 * (orig[i_col + 32 * (j_col + 32 * k_col)]));
        buf += (C1 * (orig[i_col + 1 + 32 * (j_col + 32 * k_col)] + orig[i_col - 1 + 32 * (j_col + 32 * k_col)] + orig[i_col + 32 * (j_col + 1 + 32 * k_col)] + orig[i_col + 32 * (j_col - 1 + 32 * k_col)] + orig[i_col + 32 * (j_col + 32 * (k_col + 1))] + orig[i_col + 32 * (j_col + 32 * (k_col - 1))])));
        sol[i_col + 32 * (j_col + 32 * k_col)] = buf;
      }
    }
  }
}