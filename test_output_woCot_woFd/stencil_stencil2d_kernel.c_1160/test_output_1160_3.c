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
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8184; j += 8) {
      ti = i - 8;
      tj = j - 8;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + idx][tj];
      }
      sol[i][j] = val;
    }
  }
}