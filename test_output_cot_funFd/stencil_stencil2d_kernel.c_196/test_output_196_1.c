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
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      ti = -4 * orig[i * 8192 + j] + orig[(i - 1) * 8192 + j] + orig[(i + 1) * 8192 + j] + orig[i * 8192 + j - 1] + orig[i * 8192 + j + 1];
      tj = -4 * orig[i * 8192 + j] + orig[i * 8192 + j - 1] + orig[i * 8192 + j + 1] + orig[(i - 1) * 8192 + j] + orig[(i + 1) * 8192 + j];
      val = 0;
      idx = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      while (idx < 5) {
        val += filter[idx] * (ti + tj);
        idx++;
      }
      sol[i * 8192 + j] = val;
    }
  }
}