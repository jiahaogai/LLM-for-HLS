#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[39304],double sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 3 - 1; k < 32 + 1 - 3; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 3 - 1; j < 32 + 1 - 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3 - 1; i < 32 + 1 - 3; i++) {
        i_col = i - 1 + -(32 - 1);
        j_col = j - 1 + -(32 - 1);
        k_col = k - 1 + -(32 - 1);
        tmp = orig[i + j * 39 + k * 1290] - ((0.1f * (orig[i_col + j_col * 39 + k_col * 1290] + orig[i + 1 + j * 39 + k * 1290] + orig[i + (j + 1) * 39 + k * 1290] + orig[i_col + (j_col + 1) * 39 + k_col * 1290]))) / 4.0;
        sol[i + j * 32 + k * 980] = tmp;
      }
    }
  }
}