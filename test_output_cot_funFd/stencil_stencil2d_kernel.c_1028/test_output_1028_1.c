Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 32; i++) {
      sum = 0.0;
      loopk_col:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i + (k_col - 4);
        if ((((0 <= k) && (k < 32))) && (((0 <= j) && (j < 32)))) {
          flit = (k * 32) + j;
          sum += ((double )filter[k_col]) * orig[flit];
        }
      }
      row = i * 32;
      col = j;
      sol[row + col] = sum;
    }
  }
}