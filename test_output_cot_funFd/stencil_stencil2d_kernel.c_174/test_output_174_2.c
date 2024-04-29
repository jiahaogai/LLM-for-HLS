#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 256;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = col + ((4 - (k % 3)) % 3);
        flit += filter[k] * orig[row + k_col];
      }
      sol[row + col] = flit;
    }
  }
}