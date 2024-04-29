#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      row = (j - 1) * 32 + i - 1;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        col = (k / 3) * 32 + k % 3;
        flit += orig[row * 32 + col] * filter[k];
      }
      sol[row * 32 + i - 1] = flit;
    }
  }
}