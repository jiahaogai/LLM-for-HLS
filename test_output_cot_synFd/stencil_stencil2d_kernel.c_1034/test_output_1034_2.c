#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      row = i - 1;
      col = j - 1;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        if (row + 1 + (-1 + k) >= 0 && row + 1 + (-1 + k) < 256 && col + 1 + (-1 + k) >= 0 && col + 1 + (-1 + k) < 256) {
          flit = flit + filter[k] * orig[row + 1 + (-1 + k)] * orig[col + 1 + (-1 + k)];
        }
      }
      sol[idx] = flit;
    }
  }
}