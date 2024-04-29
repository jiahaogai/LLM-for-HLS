#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      result = ((0 + filter[0]) * orig[i * 128 + j - 1]) + ((0 + filter[1]) * orig[i * 128 + j]) + ((0 + filter[2]) * orig[i * 128 + j + 1]) + ((1 + filter[3]) * orig[(i - 1) * 128 + j - 1]) + ((1 + filter[4]) * orig[(i - 1) * 128 + j]) + ((1 + filter[5]) * orig[(i - 1) * 128 + j + 1]) + ((1 + filter[6]) * orig[(i + 1) * 128 + j - 1]) + ((1 + filter[7]) * orig[(i + 1) * 128 + j]) + ((1 + filter[8]) * orig[(i + 1) * 128 + j + 1]);
      sol[i * 128 + j] = result;
    }
  }
}