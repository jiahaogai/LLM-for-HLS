#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int fidx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loop:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopj:
    for (j = 0; j < 32; j++) {
      ti = i - 1;
      tj = j - 1;
      idx = i * 32 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopf:
      for (fidx = 0; fidx < 9; fidx++) {
        val += filter[fidx] * orig[ti * 32 + tj + ((fidx / 3) - 1) * 32 + ((fidx % 3) - 1)];
      }
      sol[idx] = val;
    }
  }
}