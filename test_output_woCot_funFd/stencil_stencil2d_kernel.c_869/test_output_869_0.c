#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 256; j++) {
      result = ((0 * orig[i * 256 + j]) + (1 * orig[(i + 1) * 256 + j]) + (2 * orig[(i + 2) * 256 + j]) + (3 * orig[(i + 3) * 256 + j]) + (4 * orig[(i + 4) * 256 + j]) + (5 * orig[(i + 5) * 256 + j]) + (6 * orig[(i + 6) * 256 + j]) + (7 * orig[(i + 7) * 256 + j]) + (8 * orig[(i + 8) * 256 + j])) / 64;
      sol[i * 256 + j] = result;
    }
  }
}