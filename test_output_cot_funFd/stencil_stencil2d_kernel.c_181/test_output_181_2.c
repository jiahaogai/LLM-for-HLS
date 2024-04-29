#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner:
    for (j = 0; j < 256; j++) {
      row = i - 4;
      col = j - 4;
      k = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      inner_k:
      for (; k < 9; k++) {
        int cur_row = row + k / 5;
        int cur_col = col + k % 5;
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
        if (cur_row >= 0 && cur_row < 256 && cur_col >= 0 && cur_col < 256) {
          sol[i * 256 + j] += orig[cur_row * 256 + cur_col] * filter[k];
        }
      }
    }
  }
}