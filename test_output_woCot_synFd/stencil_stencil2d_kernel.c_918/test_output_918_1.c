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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  while (row < 64) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        for (j = -4; j <= 4; j++) {
          i = row + k;
          int _in_i;
          _in_i = i;
          if (_in_i < 0 || _in_i > 63) {
            i = 0;
          }
          
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
          for (j = -4; j <= 4; j++) {
            i = col + j;
            int _in_i;
            _in_i = i;
            if (_in_i < 0 || _in_i > 63) {
              i = 0;
            }
            t += orig[i] * filter[k + 4 + (j + 4) * 9];
          }
        }
        sol[row * 64 + col] = t;
        col++;
      }
      row++;
    }
  }
}