#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[250] = {0};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    long j_col_tmp = j - 1;
    j_col = j_col_tmp * 392;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      long k_col_tmp = k - 1;
      k_col = k_col_tmp * 392 + j_col;
      i_col = k_col;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
      for (i = 1; i < 392 + 1; i++) {
        buf[0] = orig[i_col];
        buf[250] = orig[i_col + 1];
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopk_col:
        for (k_col = k_col_tmp + 2; k_col < 392 + 1; k_col++) {
          buf[125] = orig[k_col + j_col];
          buf[126] = orig[k_col + j_col + 1];
          loopj_col:
          for (j_col = j_col_tmp + 2; j_col < 392 + 1; j_col++) {
            buf[1] = orig[j_col + k_col * 392];
            buf[2] = orig[j_col + 1 + k_col * 392];
            sol[i_col] = buf[0] / 4 + buf[1] / 2 + buf[2] / 4 + buf[250] / 4 + buf[125] / 8 + buf[126] / 8;
            i_col++;
          }
          buf[125] = buf[126];
        }
        buf[1] = buf[2];
      }
      k_col = ((k - 1) * 392) + 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopj_col:
      for (j_col = 1; j_col < 392 + 1; j_col++) {
        sol[k_col] = buf[j_col];
        k_col++;
      }
    }
  }
}