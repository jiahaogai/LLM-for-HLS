#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 1; row < 64 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    for (col = 1; col < 64 - 1; col++) {
      tid = (row - 1) * 64 + col - 1;
      flit = 0;
      loop_filter:
      for (j = 0; j < 9; j++) {
        i = (row + ((0 + j) - 4)) * 64 + (col + ((0 + j) - 4));
        flit += filter[j] * orig[i];
      }
      sol[tid] = flit;
    }
  }
}