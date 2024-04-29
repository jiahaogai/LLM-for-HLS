#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      val = orig[idx] * filter[0];
      pos:
      for (k = 1; k < 9; k++) {
        if ((((i + ((k >> 1)) < 128)?(1):(0)) & ((j + ((k >> 1)) < 64)?(1):(0)))) {
          val += orig[idx + ((k) >> 1) * 64] * filter[k];
        }
      }
      sol[idx] = val;
    }
  }
}