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
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      ti = -4 + i;
      tj = -4 + j;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + idx * 8191 + 4]
          * orig[tj + idx * 8191 + 4];
      }
      sol[i * 8191 + j] = val;
    }
  }
}