#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      result = ((-1 * filter[0]) * orig[i * 8192 + j - 8192]) + ((-1 * filter[1]) * orig[i * 8192 + j - 8191]) + ((-1 * filter[2]) * orig[i * 8192 + j - 8190]) + ((-1 * filter[3]) * orig[i * 8192 + j - 8189]) + ((-1 * filter[4]) * orig[i * 8192 + j - 8188]) + ((-1 * filter[5]) * orig[i * 8192 + j - 8187]) + ((-1 * filter[6]) * orig[i * 8192 + j - 8186]) + ((-1 * filter[7]) * orig[i * 8192 + j - 8185]) + ((-1 * filter[8]) * orig[i * 8192 + j - 8184]) + (filter[8] * orig[i * 8192 + j + 8184]);
      sol[i * 8192 + j] = result;
    }
  }
}