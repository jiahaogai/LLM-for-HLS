#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + (-1 + k);
        col = j + (-1 + k);
        if (row < 0 || row > 255 || col < 0 || col > 255) {
          t += 0;
        }
         else {
          t += orig[row * 256 + col] * filter[k];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}