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
  long tmp;
  long tmp_inner;
  long STENCIL_FIRST_Col;
  long STENCIL_ROW_Col;
  long STENCIL_INNER_Col;
  long pad;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  pad = 1;
  STENCIL_FIRST_Col = (pad - 1) + -1 + 1;
  STENCIL_ROW_Col = (pad - 1) + -1;
  STENCIL_INNER_Col = (pad - 1) + 0;
  i_col = STENCIL_FIRST_Col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  j_col = STENCIL_ROW_Col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  k_col = STENCIL_INNER_Col;
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  tmp = 32 + 1;
  tmp_inner = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  i = tmp_inner;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (j = 1; j < 32 + 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 1; k < 32 + 1; k++) {
      buf = ((pad - 1) * (pad - 1) * (pad - 1)) + ((k - 1) * (pad - 1) * (32 + 1 - 1)) + ((j - 1) * (32 + 1 - 1)) + (i - 1);
      tmp = ((pad - 1) * (pad - 1) * (pad - 1)) + ((k - 1) * (pad - 1) * (32 + 1 - 1)) + ((j - 1) * (32 + 1 - 1)) + 0;
      sol[buf] = ((2 * orig[tmp]) + (-1 * (((pad - 1) * orig[tmp + 1]) + (-1 * (orig[tmp + (pad - 1)])) + (-1 * (orig[tmp + ((pad - 1) * 2)]))))) / C0;
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      k = k_col;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 32 + 1; j++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{32}
        for (i = 1; i < 32 + 1; i++) {
          buf = ((pad - 1) * (pad - 1) * (pad - 1)) + (((k - 1) + (pad - 1) * 2) * (pad - 1) * (32 + 1 - 1)) + (((j - 1) + (pad - 1) * 2) * (32 + 1 - 1)) + (i - 1 + (pad - 1) * 2);
          tmp = ((pad - 1) * (pad - 1) * (pad - 1)) + (((k - 1) + (pad - 1) * 2) * (pad - 1) * (32 + 1 - 1)) + (((j - 1) + (pad - 1) * 2) * (32 + 1 - 1)) + (0 + (pad - 1) * 2);
          sol[buf] = ((-1 * (((pad - 1) * sol[tmp + 1]) + (-1 * (sol[tmp + (pad - 1)])) + (-1 * (sol[tmp + ((pad - 1) * 2)]))))) / C1;
        }
      }
    }
    k_col ++;
  }
  j_col ++;
}