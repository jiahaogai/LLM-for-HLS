#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      k_col = ((32 + 1) * (1 + 0)) + 1 - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = ((32 + 1) * (0 + 1)) + 1 - 1;
        j_col = ((32 + 1) * (0 + 0)) + 1 - 1;
        buf[0] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[1] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[2] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[3] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[4] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[5] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[6] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        buf[7] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
        sol[k_col] = buf[4];
        k_col--;
        sol[j_col] = buf[5] - buf[7];
        j_col--;
        sol[i_col] = buf[6] - buf[8];
        i_col--;
      }
      j_col = ((32 + 1) * (0 + 0)) + 1 - 1;
      i_col = ((32 + 1) * (0 + 1)) + 1 - 1;
      buf[0] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[1] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[2] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[3] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[4] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[5] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[6] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      buf[7] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
      sol[k_col] = buf[4];
      k_col--;
      sol[j_col] = buf[5] - buf[7];
      j_col--;
      sol[i_col] = buf[6] - buf[8];
      i_col--;
    }
    k_col = ((32 + 1) * (1 + 0)) + 1 - 1;
    i_col = ((32 + 1) * (0 + 1)) + 1 - 1;
    j_col = ((32 + 1) * (0 + 0)) + 1 - 1;
    buf[0] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[1] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[2] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[3] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[4] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[5] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[6] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    buf[7] = orig[i_col - 1] + orig[i_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[k_col - 1] + orig[k_col + 1] - 6 * orig[k_col];
    sol[k_col] = buf[4];
    k_col--;
    sol[j_col] = buf[5] - buf[7];
    j_col--;
    sol[i_col] = buf[6] - buf[8];
    i_col--;
  }
}