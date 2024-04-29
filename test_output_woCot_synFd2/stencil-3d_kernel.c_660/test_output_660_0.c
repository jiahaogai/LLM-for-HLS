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
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 392 * 0; j < 392 + 392 * 0; j++) {
    long j_col_tmp = j;
    j_col = 392 + (-1) * j_col_tmp;
    long bound_tmp = (392 + 2) * (392 + 2) * (392 + 2) - 1;
    bound = (392 + 2) * (392 + 2) - bound_tmp;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 392 * 0; k < 392 + 392 * 0; k++) {
      long k_col_tmp = k;
      k_col = 392 + (-1) * k_col_tmp;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 392 * 0; i < 392 + 392 * 0; i++) {
        long i_col_tmp = i;
        i_col = 392 + (-1) * i_col_tmp;
        t = ((C0 * (orig[i + j * 392 + k * 392 * 392])) + (C1 * (((orig[i_col + j * 392 + k * 392 * 392]) + (orig[i - 1 + j * 392 + k * 392 * 392])) + ((orig[i + (j_col) * 392 + k * 392 * 392]) + (orig[i - 1 + (j_col) * 392 + k * 392 * 392])) + ((orig[i + j * 392 + k_col * 392 * 392]) + (orig[i - 1 + j * 392 + k_col * 392 * 392]))))) / ((long )4);
        sol[i + j * 392 + k * 392 * 392] = t;
      }
    }
  }
}