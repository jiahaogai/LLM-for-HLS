#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long tmp;
  long tmp_col;
  long C0_sq;
  long C1_sq;
  long C2_sq;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  C0_sq = C0 * C0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  C1_sq = C1 * C1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  C2_sq = C2 * C2;
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    i_col = i * C0;
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      j_col = j * C1;
      for (k = 0; k < 40; k++) {
        k_col = k * C2;
        tmp = 0;
        tmp_col = 0;
        for (x = 0; x < C0; x++) {
          buf[x] = orig[i_col + x + ((j_col + 0 * C1) + (k_col + 0 * C2))];
          tmp_col += buf[x];
        }
        for (x = 0; x < C1; x++) {
          tmp += buf[x + C0];
        }
        sol[i_col + j_col + k_col] = (tmp_col + tmp) / ((C0_sq + 1) * (C1_sq + 1) * (C2_sq + 1));
      }
    }
  }
}