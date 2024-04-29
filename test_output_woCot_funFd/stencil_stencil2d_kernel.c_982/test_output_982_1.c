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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (row = -1; row < 2; row++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        middle_flatten:
        for (col = -1; col < 2; col++) {
          flatten_row = i + row;
          flatten_col = j + col;
          if (flatten_row < 0 || flatten_row > 255 || flatten_col < 0 || flatten_col > 255) {
            t += 0;
          }
           else {
            t += orig[flatten_row * 256 + flatten_col] * filter[row * 3 + col + 1];
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}