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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 33; col++) {
      t = 0;
      loop_k:
      for (k = -4; k < 5; k++) {
        i = row + k;
        if (i < 1 || i > 32) {
          continue;
        }
        loop_j:
        for (j = -4; j < 5; j++) {
          if (((col + j) < 1) || ((col + j) > 32)) {
            continue;
          }
          t += ((int )filter[((k + 4) * 9) + (j + 4)]) * orig[i * 32 + (col + j)];
        }
      }
      sol[row * 32 + col] = t;
    }
  }
}