- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Automatically execute the `sol` array index assignments concurrently.
#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{2}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        row = ((4 + i) + k);
        if (row < 0) {
          row = 0;
        }
        if (row > 255) {
          row = 255;
        }
        col = ((4 + j) + k);
        if (col < 0) {
          col = 0;
        }
        if (col > 255) {
          col = 255;
        }
        t += ((filter[5 - (k + 4)]) * orig[row * 256 + col]);
      }
      sol[i * 256 + j] = t;
    }
  }
}