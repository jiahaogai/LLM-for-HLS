#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = orig[idx] * filter[0];
      
      inner:
      for (k = 1; k < 9; k++) {
        if ((((i + k - 1) < 256) && ((j + k - 1) < 256)) && (((i + k - 1) >= 0) && ((j + k - 1) >= 0))) {
          val += orig[idx + (k << 8)] * filter[k];
        }
      }
      sol[idx] = val;
    }
  }
}