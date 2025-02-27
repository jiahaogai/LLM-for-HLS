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
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      val = 0;
      ti = i - 8;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (tj = j - 8; tj < j + 8; ++tj) {
        idx = ti * 8192 + tj;
        val += orig[idx] * filter[tj - j + 8];
      }
      sol[i * 8192 + j] = val;
    }
  }
}