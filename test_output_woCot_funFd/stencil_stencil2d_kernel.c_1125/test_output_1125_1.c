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
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + i_col;
        if ((((i_col >= 0) && (i_col < 8)) && ((k_col >= 0) && (k_col < 8))) && ((k >= 0) && (k < 8192))) {
          sum += filter[k_col] * orig[k];
        }
        k_col++;
      }
      sol[j] = sum;
      sum = 0.0;
    }
  }
}