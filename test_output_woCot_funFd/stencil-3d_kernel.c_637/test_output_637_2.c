**TODO:**
 - Complete this kernel by filling in the code for the `stencil3d` function.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 392 * 0; j < 1 + 392 * 128; j += 392 * 128) {
    loopk_col:
/* Standardize from: for(k_col = 0;k_col < 128;k_col++) {...} */
    for (k_col = 0; k_col <= 127; k_col++) {
      buf[k_col] = orig[k_col + 0 + (j + 0) * 128];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 128;k++) {...} */
    for (k = 1; k < 128; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 128;i++) {...} */
      for (i = 1; i < 128; i++) {
        i_col = i + 0 + (k + 0) * 128;
        j_col = j + 0 + (k + 1) * 128;
        k_col = k + 0 + (i + 1) * 128;
        sol[i_col] = 0.125 * (buf[k_col] + buf[j_col] + buf[k_col - 1] + buf[j_col - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_bottom:
/* Standardize from: for(k = 128 + 1;k < 256;k++) {...} */
    for (k = 128 + 1; k < 256; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_bottom:
/* Standardize from: for(i = 128 + 1;i < 256;i++) {...} */
      for (i = 128 + 1; i < 256; i++) {
        i_col = i + 0 + (k + 0) * 128;
        j_col = j + 128 + (k + 1) * 128;
        k_col = k + 0 + (i + 1) * 128;
        sol[i_col] = 0.125 * (buf[k_col] + buf[j_col] + buf[k_col - 1] + buf[j_col - 1]);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_bottom:
/* Standardize from: for(j = 392 + 1;j < 512;j++) {...} */
  for (j = 392 + 1; j < 512; j++) {
    loopk_col_bottom:
/* Standardize from: for(k_col = 0;k_col < 128;k_col++) {...} */
    for (k_col = 0; k_col <= 127; k_col++) {
      buf[k_col] = orig[k_col + 0 + (j + 0) * 128];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_bottom_1:
/* Standardize from: for(k = 128 + 1;k < 256;k++) {...} */
    for (k = 128 + 1; k < 256; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_bottom_1:
/* Standardize from: for(i = 128 + 1;i < 256;i++) {...} */
      for (i = 128 + 1; i < 256; i++) {
        i_col = i + 0 + (k + 0) * 128;
        j_col = j + 128 + (k + 1) * 128;
        k_col = k + 0 + (i + 1) * 128;
        sol[i_col] = 0.125 * (buf[k_col] + buf[j_col] + buf[k_col - 1] + buf[j_col - 1]);
      }
    }
  }
}