#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + 4 - 2 + (j + 4 - 2) * 128 + k * 128];
      }
      sol[i * 64 + j] = sum;
    }
  }
}