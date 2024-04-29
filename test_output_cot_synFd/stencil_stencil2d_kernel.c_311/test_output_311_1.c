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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      i_col = i * 64;
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{14}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = i_col + k * 8;
        sum += filter[k] * orig[k_col + j];
      }
      sol[i_col + j] = sum;
    }
  }
}