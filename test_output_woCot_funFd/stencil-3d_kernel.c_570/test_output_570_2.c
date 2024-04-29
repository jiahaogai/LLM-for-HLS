#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long pad_orig[39296];
  
#pragma ACCEL PAD pad_orig{orig}
  long pad_sol[32768];
  
#pragma ACCEL PAD pad_sol{sol}
  for (k = 0; k < 4; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 4; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      for (i = 0; i < 4; i++) {
        i_col = i - 1 + ((j - 1) * 4) + ((k - 1) * 16);
        k_col = k - 1;
        pad_orig[i_col + 4 * j + 4 * 4 * k_col] = orig[i + 4 * j + 4 * 4 * k];
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 4; j++) {
      
#pragma ACCEL PIPELINE auto{}
      for (i = 0; i < 4; i++) {
        i_col = i - 1 + ((j - 1) * 4) + ((k - 1) * 16);
        k_col = k - 1;
        pad_sol[i_col + 4 * j + 4 * 4 * k_col] = ((((pad_orig[i_col + 4 * (j - 1) + 4 * 4 * k_col] + pad_orig[i_col + 4 * (j + 1) + 4 * 4 * k_col]) + pad_orig[i_col + 4 * j + 4 * 4 * (k_col - 1)]) + pad_orig[i_col + 4 * j + 4 * 4 * (k_col + 1)]) + pad_orig[i_col + 4 * j + 4 * 4 * k_col]) / 256;
      }
    }
  }
}