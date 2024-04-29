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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      result = ((0 * orig[8 * i + j]) + (1 * orig[8 * i + j + 1]) + (2 * orig[8 * i + j + 2]) + (3 * orig[8 * (i + 1) + j]) + (4 * orig[8 * (i + 1) + j + 1]) + (5 * orig[8 * (i + 1) + j + 2]) + (6 * orig[8 * (i + 2) + j]) + (7 * orig[8 * (i + 2) + j + 1]) + (8 * orig[8 * (i + 2) + j + 2])) / 64;
      sol[8 * i + j] = result;
    }
  }
}