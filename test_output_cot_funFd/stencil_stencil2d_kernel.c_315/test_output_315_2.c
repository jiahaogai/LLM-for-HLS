#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 8192; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + kernel_offsets[k] + ((j + kernel_offsets[k]) * 8192)] ;
      }
      sol[i * 8192 + j] = result;
      result = 0;
    }
  }
}