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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      ti = i - 1;
      if (ti < 0) {
        ti = 0;
      }
      tj = j - 1;
      if (tj < 0) {
        tj = 0;
      }
      val = 0;
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti * 256 + tj + idx_neigh[idx]];
      }
      sol[i * 256 + j] = val;
    }
  }
}