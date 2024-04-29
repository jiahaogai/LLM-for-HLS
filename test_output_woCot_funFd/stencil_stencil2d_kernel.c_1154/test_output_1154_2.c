#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (r = 0; r < 256; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (c = 0; c < 256; c++) {
      tmp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      inner:
      for (i = -1 + 0; i < 1 + 0; i++) {
        
#pragma ACCEL PIPELINE auto{off}
        inner_1:
        for (j = -1 + 0; j < 1 + 0; j++) {
          row = r + i;
          col = c + j;
          if (row < 0 || 256 <= row || col < 0 || 256 <= col) {
            tmp += orig[0];
          }
          
#pragma ACCEL FACTOR=auto{1}
          else {
            tmp += orig[row * 256 + col] * filter[i + 1];
          }
        }
      }
      flatten_row = r >> 2;
      flatten_col = c >> 2;
      sol[flatten_row * 64 + flatten_col] = tmp;
    }
  }
}