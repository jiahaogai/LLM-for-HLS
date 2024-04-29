#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      ti = ((8 * i) - 1) + 0;
      tj = ((8 * j) - 1) + 0;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + align[idx] + tj + align[idx]];
      }
      sol[i * 8192 + j] = val;
    }
  }
}