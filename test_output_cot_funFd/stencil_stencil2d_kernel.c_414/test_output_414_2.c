#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (min_i = -1 * pad; min_i <= 1 * pad; min_i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (min_j = -1 * pad; min_j <= 1 * pad; min_j++) {
          max_i = 8 - min_i;
          max_j = 8 - min_j;
          t += filter[static_cast<int>(round(sqrt(static_cast<double>(min_i * min_i + min_j * min_j)) * 16.0))] * orig[i * 8 + max_i - pad] * orig[j * 8 + max_j - pad];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}