#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8; j++) {
      row = i - 4 + 0;
      col = j - 4 + 0;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (flatten_row = 0; flatten_row < 5; flatten_row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (flatten_col = 0; flatten_col < 5; flatten_col++) {
          int orig_idx = (row + flatten_row) * 8 + col + flatten_col;
          t += filter[flatten_row * 5 + flatten_col] * orig[orig_idx];
        }
      }
      sol[i * 8 + j] = t;
    }
  }
}