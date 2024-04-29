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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        for (j = -4; j <= 4; j++) {
          i = row + k;
          int _in_bound_i = i >= 0 && i < 32;
          j = col + j;
          int _in_bound_j = j >= 0 && j < 32;
          int _in_bound = _in_bound_i && _in_bound_j;
          t += filter[k + 4] * orig[i * 32 + j] * (_in_bound ? 1 : 0);
        }
      }
      sol[row * 32 + col] = t;
      col++;
    }
    row++;
  }
}