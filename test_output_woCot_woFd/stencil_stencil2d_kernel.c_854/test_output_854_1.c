#pragma ACCEL kernel stencil

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
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      i_col = i - 4;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        if (((i_col + k) >= 0) && ((i_col + k) < 256)) {
          sum = 0.0;
          operand:
          for (k = 0; k < 9; k++) {
            if(((j + k) >= 0) && ((j + k) < 256)) {
              sum += filter[k] * orig[i_col + k][j + k];
            }
          }
          sol[i][j] = sum;
        }
        k_col++;
      }
    }
  }
}