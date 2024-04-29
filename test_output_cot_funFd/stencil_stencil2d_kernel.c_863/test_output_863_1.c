#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int offset;
  int base;
  int v;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 32; j++) {
      v = 0;
      inner:
      for (offset = -4; offset < 5; offset++) {
        base = (i * 32 + j) * 32 + offset;
        v += filter[4 + offset] * orig[base];
      }
      sol[i * 32 + j] = v;
    }
  }
}