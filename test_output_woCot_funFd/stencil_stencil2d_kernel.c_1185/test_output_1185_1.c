Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = ((0 * orig[index(i - 1,j - 1)]) + (1 * orig[index(i - 1,j)]) + (0 * orig[index(i - 1,j + 1)]) + (1 * orig[index(i,j - 1)]) + (2 * orig[index(i,j)]) + (1 * orig[index(i,j + 1)]) + (0 * orig[index(i + 1,j - 1)]) + (1 * orig[index(i + 1,j)]) + (0 * orig[index(i + 1,j + 1)])) / 16;
      sol[index(i,j)] = result;
    }
  }
}