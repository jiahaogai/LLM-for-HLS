#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long R_low;
  long R_high;
  long C_low;
  long C_high;
  long K_low;
  long K_high;
  R_low = 1;
  R_high = 392;
  C_low = 1;
  C_high = 392;
  K_low = 1;
  K_high = 4;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = K_low; k <= K_high - 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = C_low; j <= C_high - 1; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = R_low; i <= R_high - 1; i++) {
        k_col = ((k - 1) * (C_high - C_low + 1)) + (j - 1);
        i_col = ((i - 1) * (C_high - C_low + 1)) + (j - 1);
        idx = i * (C_high - C_low + 1) + j;
        idx_col = k_col * (C_high - C_low + 1) + i_col;
        sol[idx] = ((C0 * orig[idx_col]) + (C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + (C_high - C_low + 1)] + orig[idx_col - (C_high - C_low + 1)]))) / (C1 * 4);
      }
    }
  }
//#pragma endscop
}