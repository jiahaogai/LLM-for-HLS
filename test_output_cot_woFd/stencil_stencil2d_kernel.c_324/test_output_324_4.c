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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64 + 2; j++) {
      ti = i - 1;
      tj = j - 1;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + idx * 128 + tj];
      }
      sol[i * 128 + j] = val;
    }
  }
}