#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
  for (k = 1; k < 32 + 1 - 4; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1 - 4; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1 - 4; i++) {
        i_col = i - 1 + ((j - 1) * (32 + 4)) + ((k - 1) * (32 + 4) * (32 + 4));
        j_col = j - 1 + ((k - 1) * (32 + 4));
        k_col = k - 1;
        t = (C0 * (orig[i_col - 1] + orig[i_col + 1] + orig[i_col + (32 + 4) * 2] + orig[i_col - (32 + 4) * 2])) + (C1 * (orig[i_col] + orig[i_col + (32 + 4)] + orig[i_col + 2] + orig[i_col - 2])) + orig[i_col];
        sol[i_col] = t;
      }
    }
  }
}