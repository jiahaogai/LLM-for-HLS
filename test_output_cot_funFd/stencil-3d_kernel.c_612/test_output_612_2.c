#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long filter;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 30; k_col++) {
      loopi_col:
      for (i_col = 0; i_col < 30; i_col++) {
        j_col = 1 + 32 - 1 + k_col;
        filter = ((((orig[i_col + 0 + 3900 * (j_col)]) + (orig[i_col + 1 + 3900 * (j_col)]))) + ((orig[i_col + 3900 * (j_col)] + orig[i_col + 3 + 3900 * (j_col)]))) + (((orig[i_col + 30 + 3900 * (j_col)] + orig[i_col + 31 + 3900 * (j_col)]) + (orig[i_col + 3900 * (j_col)] + orig[i_col + 1 + 3900 * (j_col)])));
        filter >>= 3;
        sol[i_col + 0 + 3200 * (j_col)] = filter;
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 30 + 1 - 3; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 30 + 1 - 3; i++) {
        j = 1 + 30 - 1 + k;
        filter = ((((sol[i + 0 + 3200 * (j)]))) + (((sol[i + 1 + 3200 * (j)] + sol[i + 3200 * (j)])))) + (((sol[i + 3200 * (j)] + sol[i + 3 + 3200 * (j)])));
        filter >>= 3;
        sol[i + 1600 * (k + 1)] = filter;
      }
    }
  }
}