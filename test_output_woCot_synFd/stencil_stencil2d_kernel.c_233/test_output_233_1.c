Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_col:
    for (col = 1; col < 33; col++) {
      t = 0;
      loop_elem:
      for (i = -1 + row; i <= 1 + row; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_inner_elem:
        for (j = -1 + col; j <= 1 + col; j++) {
          t += filter[((i + 1) * 3) + (j + 1)] * orig[i * 33 + j];
        }
      }
      sol[row * 33 + col] = t;
    }
  }
}