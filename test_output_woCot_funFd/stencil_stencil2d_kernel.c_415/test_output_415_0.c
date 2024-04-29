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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        if (((i_col + k_col) < 0) || ((i_col + k_col) > 255)) {
          sum = 0.0;
        }
         else {
          sum = orig[i_col + k_col] * filter[k_col];
        }
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        k_col++;
        sum += orig[i_col + k_col] * filter[k_col];
        sol[i * 256 + j] = sum;
      }
    }
  }
}