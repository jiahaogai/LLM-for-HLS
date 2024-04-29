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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      ti = ((8 * i) - 1) + 0;
      tj = ((8 * j) - 1) + 0;
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + _idx_[idx] + tj];
      }
      sol[i * 8192 + j] = val;
    }
  }
}