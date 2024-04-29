#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        k_col = k + j;
        if (k_col < 0) {
          k_col = 0;
        }
        if (k_col > 8191) {
          k_col = 8191;
        }
        i_col = i - 4;
        if (i_col < 0) {
          i_col = 0;
        }
        if (i_col > 8191) {
          i_col = 8191;
        }
        sum += filter[k + 4] * orig[k_col * 8192 + i_col];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}