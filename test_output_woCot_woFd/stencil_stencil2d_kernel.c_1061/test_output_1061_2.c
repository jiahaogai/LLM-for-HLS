#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = ((0 + filter[0]) * orig[i * 256 + j]) + ((0 + filter[1]) * orig[i * 256 + j + 1]) + ((0 + filter[2]) * orig[(i + 1) * 256 + j]) + ((0 + filter[3]) * orig[(i + 1) * 256 + j + 1]) + ((0 + filter[4]) * orig[(i + 2) * 256 + j]) + ((0 + filter[5]) * orig[(i + 2) * 256 + j + 1]) + ((0 + filter[6]) * orig[(i + 3) * 256 + j]) + ((0 + filter[7]) * orig[(i + 3) * 256 + j + 1]) + ((0 + filter[8]) * orig[(i + 4) * 256 + j]);
      sol[i * 256 + j] = result;
    }
  }
}