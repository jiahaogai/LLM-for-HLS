#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 9; k++) {
        val += orig[idx + k - 1] * filter[k];
      }
      sol[idx] = val;
    }
  }
}