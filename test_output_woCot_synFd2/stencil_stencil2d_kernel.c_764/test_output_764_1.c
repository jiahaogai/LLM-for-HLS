#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 16; i < 8172; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 16; j < 8172; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k_col = j - 4; k_col <= j + 4; k_col++) {
        i_col = i - 4 + (k_col - j);
        sum += filter[((k_col - j) + 4)] * orig[i_col * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}