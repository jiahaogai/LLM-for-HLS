Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int col;
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (row = 2; row < 128 - 2; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (col = 2; col < 64 - 2; col++) {
      temp = 0;
      inner:
      for (k_row = 0; k_row < 3; k_row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_middle:
        for (k_col = 0; k_col < 3; k_col++) {
          k = (k_row * 3) + k_col;
          temp += filter[k] * orig[((row - 2) + k_row) * 64 + (col - 2) + k_col];
        }
      }
      sol[row * 64 + col] = temp;
    }
  }
}