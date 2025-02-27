#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter:
      for (k = 0; k < 9; k++) {
        val += orig[idx + ((k - 4) * 256)] * filter[k];
      }
      sol[idx] = val;
    }
  }
}