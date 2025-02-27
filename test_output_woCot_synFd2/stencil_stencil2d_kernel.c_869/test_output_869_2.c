#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  while (row < 256) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
	for (j = -4; j < 5; j++) {
          i = row + k;
          int i_row;
          int i_col;
          i_row = i / 32;
          i_col = i % 32;
          t += filter[k + 4] * orig[i_row * 32 + i_col + j + 4];
        }
      }
      sol[row * 256 + col] = t;
      col++;
    }
    row++;
  }
}