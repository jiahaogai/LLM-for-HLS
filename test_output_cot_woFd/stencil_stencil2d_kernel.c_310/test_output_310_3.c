#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = -4; k <= 4; k++) {
        k_col = i + k;
        if (k_col < 0) {
          k_col = 0;
        }
        
#if 0
          if (k_col > 8191) {
            k_col = 8191;
          }
#endif
        k_row = j + k;
        if (k_row < 0) {
          k_row = 0;
        }
        
#if 0
          if (k_row > 8191) {
            k_row = 8191;
          }
#endif
        sum += filter[k + 4] * orig[k_row * 8192 + k_col];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}