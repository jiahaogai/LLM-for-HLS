#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      result = ((0 * orig[i * 256 + j]) + (1 * orig[i * 256 + j + 1]) + (2 * orig[i * 256 + j + 2]) + (3 * orig[i * 256 + j + 256]) + (4 * orig[i * 256 + j + 257]) + (5 * orig[i * 256 + j + 258]) + (6 * orig[i * 256 + j + 256 + 1]) + (7 * orig[i * 256 + j + 256 + 2]) + (8 * orig[i * 256 + j + 256 + 3])) / 64;
      sol[i * 256 + j] = result;
    }
  }
}