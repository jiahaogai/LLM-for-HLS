#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        bound = (392 + 2) * (392 + 2);
        t = 0;
        t = orig[i_col + (j_col + (k_col + (392 + 2) * 392)) * (392 + 2)];
        sol[i + j * 392 + k * 392 * 392] = (((t + orig[i_col + (j_col + (k_col - 1 + (392 + 2) * 392)) * (392 + 2)]) + orig[i_col + (j_col - 1 + (k_col + (392 + 2) * 392)) * (392 + 2)]) + orig[i_col - 1 + (j_col + (k_col + (392 + 2) * 392)) * (392 + 2)]) + orig[i_col - 1 + (j_col - 1 + (k_col + (392 + 2) * 392)) * (392 + 2)] - 8 * t + orig[i_col + (j_col + (k_col + (392 + 2) * 392)) * (392 + 2)];
      }
    }
  }
}