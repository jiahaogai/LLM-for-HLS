#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      row = i - 1;
      col = j - 1;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (((row + 0 >= 0) && (row + 0 < 128)) && ((col + ((k + 0) % 3 - 1)) >= 0) && ((col + ((k + 0) % 3 - 1)) < 64)) {
          flit = flit + filter[k] * orig[row + 0][col + ((k + 0) % 3 - 1)] ;
        }
        
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{1}
        if (((row + 1 >= 0) && (row + 1 < 128)) && ((col + ((k + 1) % 3 - 1)) >= 0) && ((col + ((k + 1) % 3 - 1)) < 64)) {
          flit = flit + filter[k] * orig[row + 1][col + ((k + 1) % 3 - 1)] ;
        }
        
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{1}
        if (((row + 0 >= 0) && (row + 0 < 128)) && ((col + ((k + 2) % 3 - 1)) >= 0) && ((col + ((k + 2) % 3 - 1)) < 64)) {
          flit = flit + filter[k] * orig[row + 0][col + ((k + 2) % 3 - 1)] ;
        }
      }
      sol[i][j] = flit;
    }
  }
}