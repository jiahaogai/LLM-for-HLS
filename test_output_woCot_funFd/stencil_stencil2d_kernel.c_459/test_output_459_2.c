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
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    loopi:
    for (i = 1; i < 8191; i++) {
      row = ((8 * j) - 1);
      col = ((8 * i) - 1);
      flit = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        flit += ((orig[(((row + ((k / 3))) * 8) + (col + ((k % 3))))] * filter[k]));
      }
      sol[(((8 * j) - 1) * 8) + ((8 * i) - 1)] = flit;
    }
  }
}