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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      col = j * 8;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (flatten_row = 0; flatten_row < 8; flatten_row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        inner_1:
        for (flatten_col = 0; flatten_col < 8; flatten_col++) {
          int x = row + flatten_row;
          int y = col + flatten_col;
          t += orig[x * 64 + y] * filter[flatten_row * 8 + flatten_col];
        }
      }
      sol[row * 64 + col] = t;
    }
  }
}