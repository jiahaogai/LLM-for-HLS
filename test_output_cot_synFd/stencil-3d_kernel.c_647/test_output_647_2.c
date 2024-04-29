#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long kj;
  long ki;
  long index;
  long result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1 + 0; i < 33 + 0; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1 + 0; j < 33 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1 + 0; k < 33 + 0; k++) {
        k_col = 32 + 0 - k;
        j_col = 32 + 0 - j;
        i_col = 32 + 0 - i;
        index = i * 32 * 32 + j * 32 + k;
        result = ((C0 * (orig[index])) + (C1 * (((orig[index + 1] + orig[index - 1]) + (orig[index + 32] + orig[index - 32])) + (orig[index + 32 * 32] + orig[index - 32 * 32]))));
        sol[index] = result;
      }
    }
  }
}