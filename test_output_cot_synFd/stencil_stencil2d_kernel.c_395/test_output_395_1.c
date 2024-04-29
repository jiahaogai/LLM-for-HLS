#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 1; j < 32 + 1; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (((32 + 1) * (k - 1)) + j) - 1;
        s += filter[k] * orig[idx];
      }
      sol[((32 + 1) * (i - 1)) + j] = s;
    }
  }
}