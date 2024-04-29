#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      row = i - 4;
      col = j - 4;
      flatten_row = row * 256;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (row + ((k / 3) * 8) < 0 || row + ((k / 3) * 8) > 255 || col + ((k % 3) * 8) < 0 || col + ((k % 3) * 8) > 255) {
          sol[flatten_row + col + ((k % 3) * 8)] = orig[flatten_row + col];
        }
else {
          sol[flatten_row + col + ((k % 3) * 8)] = orig[flatten_row + col] + filter[k];
        }
      }
    }
  }
}