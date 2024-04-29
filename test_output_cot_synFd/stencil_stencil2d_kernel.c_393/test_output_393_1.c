#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 256; j++) {
      result = 0;
      middle:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-4 + k) + ((j + (-4 + k)) * 256)];
      }
      sol[i + j * 256] = result;
    }
  }
}