Code: ### Function Body:

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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sp_row:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    sp_col:
    for (j = 0; j < 32; j++) {
      row = i * 32;
      col = j * 32;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{1}
      filter_elem:
      for (k = 0; k < 9; k++) {
        flit += orig[row + k / 32][col + k % 32] * filter[k];
      }
      sol[row + 1 + 32 / 2][col + 1 + 32 / 2] = flit;
    }
  }
}