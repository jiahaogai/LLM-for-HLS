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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 16; i < 8172; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 16; j < 8172; j++) {
      i_col = i - 16 + 0;
      k_col = j - 16 + 0;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i_col + align(k, 16, 8192)] * orig[k_col + align(k, 16, 8192)];
      }
      sol[i + align(j, 16, 8192)] = sum;
    }
  }
}