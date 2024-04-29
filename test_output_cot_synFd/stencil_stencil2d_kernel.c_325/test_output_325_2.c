#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 16; i < 8172 - 16; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 16; j < 8172 - 16; j++) {
      result = 0;
      middle:
      for (k = -4; k < 5; k++) {
        result += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = result;
    }
  }
}