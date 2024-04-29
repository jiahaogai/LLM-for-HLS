#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int temp_row;
  int temp_col;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8; j++) {
      temp_row = i - 4 + 0;
      temp_col = j - 4 + 0;
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      inner:
      for (k = 0; k < 5; k++) {
        
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
        for (k_col = 0; k_col < 5; k_col++) {
          row = temp_row + k;
          col = temp_col + k_col;
          if (row < 0 || 8 < row || col < 0 || 8 < col) {
            continue;
          }
          result += ((int )filter[k * 5 + k_col]) * orig[row * 8 + col];
        }
      }
      sol[i * 8 + j] = result;
    }
  }
}