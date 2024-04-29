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
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8188; j++) {
      result = ((0 + filter[0]) * orig[i * 8192 + j]) + ((0 + filter[1]) * orig[i * 8192 + j + 1]) + ((0 + filter[2]) * orig[i * 8192 + j + 2]) + ((0 + filter[3]) * orig[i * 8192 + j + 16]) + ((0 + filter[4]) * orig[i * 8192 + j + 17]) + ((0 + filter[5]) * orig[i * 8192 + j + 18]) + ((0 + filter[6]) * orig[i * 8192 + j + 32]) + ((0 + filter[7]) * orig[i * 8192 + j + 33]) + ((0 + filter[8]) * orig[i * 8192 + j + 34]);
      sol[i * 8192 + j] = result;
    }
  }
}