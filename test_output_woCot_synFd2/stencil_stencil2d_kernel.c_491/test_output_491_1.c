#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
          val += orig[cur_i * 256 + cur_j] * filter[idx];
        }
      }
      sol[i * 256 + j] = val;
    }
  }
}