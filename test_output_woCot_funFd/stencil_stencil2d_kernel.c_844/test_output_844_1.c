#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = i - 4; k <= i + 4; k++) {
        if (k < 0) {
          k = -k;
          k_col = 8192 + k_col;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (k > 8191) {
          k = 2 * 8191 - k;
          k_col = 8192 + k_col;
        }
        buf[k_col++] = orig[k * 8192 + j];
      }
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i * 8192 + j] += filter[k] * buf[k];
      }
    }
  }
}