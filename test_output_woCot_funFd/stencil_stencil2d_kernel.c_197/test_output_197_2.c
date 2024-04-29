#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
=======
  int ti;
  int tj;
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    row = i & 7;
    row_up = (row - 1 + 8) % 8;
    row_down = (row + 1) % 8;
    col = i & 511;
    col_up = (col - 1 + 512) % 512;
    col_down = (col + 1) % 512;
    t = 0;
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + ((j - 4) % 8) * 512 + ((j - 4) / 8) * 8192];
    }
    sol[i] = t;
=======
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (idx = 0; idx < 9; ++idx) {
        int cur_i = ti + idx / 5;
        int cur_j = tj + idx % 5;
        if (cur_i >= 0 && cur_i < 256 && cur_j >= 0 && cur_j < 256) {
          val += filter[idx] * orig[cur_i * 256 + cur_j];
        }
      }
      sol[i * 256 + j] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}