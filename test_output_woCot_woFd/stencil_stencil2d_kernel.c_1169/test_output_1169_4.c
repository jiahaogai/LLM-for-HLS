#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i * 8192 + j] * filter[0]) + (orig[i * 8192 + j + 1] * filter[1]) + (orig[i * 8192 + j + 8192] * filter[2]) + (orig[i * 8192 + j - 1] * filter[3]) + (orig[i * 8192 + j - 8192] * filter[4]) + (orig[(i - 1) * 8192 + j] * filter[5]) + (orig[(i + 1) * 8192 + j] * filter[6]) + (orig[(i - 8192) * 8192 + j] * filter[7]) + (orig[(i + 8192) * 8192 + j] * filter[8])) / 4096;
      sol[i * 8192 + j] = result;
    }
  }
}