#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (64 * (k - 4)) + j;
        s += filter[k] * orig[i * 64 + idx];
      }
      sol[i * 64 + j] = s;
    }
  }
}