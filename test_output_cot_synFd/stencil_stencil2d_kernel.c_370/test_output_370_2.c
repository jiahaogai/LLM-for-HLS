#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int row;
  int col;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      row = i - 4 + ((0 <= (i - 4)) ? 0 : 256);
      col = j - 4 + ((0 <= (j - 4)) ? 0 : 256);
      inner:
      for (k = 0; k < 9; k++) {
        fl = row + ((0 <= ((8 - k) + row)) ? (8 - k) + row : 0);
        sol[idx] += filter[k] * orig[fl * 256 + col];
      }
    }
  }
}