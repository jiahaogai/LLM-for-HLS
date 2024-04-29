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
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        sum = ((orig[i_col + 0] * filter[k_col + 0]) + (orig[i_col + 1] * filter[k_col + 1]) + (orig[i_col + 2] * filter[k_col + 2]) + (orig[i_col + 3] * filter[k_col + 3]) + (orig[i_col + 4] * filter[k_col + 4]) + (orig[i_col + 5] * filter[k_col + 5]) + (orig[i_col + 6] * filter[k_col + 6]) + (orig[i_col + 7] * filter[k_col + 7]) + (orig[i_col + 8] * filter[k_col + 8]));
        sol[j] = sum;
        k_col++;
        i_col++;
      }
    }
  }
}