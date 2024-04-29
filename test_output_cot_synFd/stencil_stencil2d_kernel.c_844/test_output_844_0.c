#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 16;
      sol[row + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        flit = filter[k] * orig[row + col + ((k + 2) % 3) - 1];
        sol[row + col] += flit;
      }
    }
  }
}