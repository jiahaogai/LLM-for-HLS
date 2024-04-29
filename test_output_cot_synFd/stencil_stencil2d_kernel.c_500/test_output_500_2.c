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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (row < 256) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j = -4; j < 5; j++) {
          i = row + k;
          int _in_i;
          _in_i = i;
          if (_in_i < 0 || _in_i >= 256) {
            i = 0;
          }
          j = col + j;
          int _in_j;
          _in_j = j;
          if (_in_j < 0 || _in_j >= 256) {
            j = 0;
          }
          t += filter[k + 4] * orig[i * 256 + j] ;
        }
      }
      sol[row * 256 + col] = t;
      col++;
    }
    row++;
  }
}