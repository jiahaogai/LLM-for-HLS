#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flatten_filter[81];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 8; i < 8184; i += 8) {
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      inner:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{62}
        for (col = -1; col <= 1; col++) {
          t += orig[i + row * 8 + col] * filter[row + 1 * 3 + col + 1];
        }
      }
      sol[i / 8 + j / 8 * 64] = t;
    }
  }
}