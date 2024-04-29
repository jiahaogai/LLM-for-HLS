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
  long idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
    for (j = 1; j < 33; j++) {
      loop_k:
      for (k = 1; k < 33; k++) {
        k_col = ((33 * (k - 1)) + 1);
        j_col = ((33 * (j - 1)) + 1);
        i_col = ((33 * (i - 1)) + 1);
        buf = ((((C0 * (orig[k_col - 1] + orig[k_col + 1]))) + (((C1 * (orig[j_col - 1] + orig[j_col + 1]))) + (((orig[i_col - 1] + orig[i_col + 1]) * 4)))) / 32);
        idx = ((33 * (k - 1)) + j);
        sol[idx] = buf;
      }
    }
  }
}