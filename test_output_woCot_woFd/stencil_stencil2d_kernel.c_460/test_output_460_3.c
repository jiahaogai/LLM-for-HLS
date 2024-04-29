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
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      k_col = -4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k_col < 5) {
        i_col = -4;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        while (i_col < 5) {
          k = k_col + i;
          if (k < 0) {
            k = -k;
          }
          if (k > 8191) {
            k = 8191;
          }
          i_col += 8;
          sum += filter[k_col + 4] * orig[k * 8 + i_col + 4];
        }
        k_col += 8;
      }
      sol[i * 8 + j] = sum;
    }
  }
}