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
  long delta;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 40; k++) {
        i_col = i - 1;
        if (i == 0) {
          i_col = i;
        }
        j_col = j - 1;
        if (j == 0) {
          j_col = j;
        }
        k_col = k - 1;
        if (k == 0) {
          k_col = k;
        }
        buf = ((C0 * (long )orig[i * 40 + j * 4 + k]) + (C1 * (long )(orig[i_col * 40 + j * 4 + k] + orig[i * 40 + j_col * 4 + k] + orig[i * 40 + j * 4 + k_col])));
        sol[i * 40 + j * 4 + k] = buf;
      }
    }
  }
}