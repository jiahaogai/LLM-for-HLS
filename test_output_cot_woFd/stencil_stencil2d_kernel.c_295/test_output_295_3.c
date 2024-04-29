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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      col = j * 8;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        flit += orig[row + k / 8] * filter[k] * sol[col + k % 8];
      }
      sol[col + 8] = flit;
    }
  }
}