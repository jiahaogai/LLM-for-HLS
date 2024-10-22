#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8178; j++) {
      result = ((0 + filter[0]) * orig[i * 8192 + j]) + ((0 + filter[1]) * orig[i * 8192 + j + 8178]) + ((0 + filter[2]) * orig[i * 8192 + j + 8178 * 2]) + ((0 + filter[3]) * orig[i * 8192 + j + 8178 * 3]) + ((0 + filter[4]) * orig[i * 8192 + j + 8178 * 4]) + ((0 + filter[5]) * orig[i * 8192 + j + 8178 * 5]) + ((0 + filter[6]) * orig[i * 8192 + j + 8178 * 6]) + ((0 + filter[7]) * orig[i * 8192 + j + 8178 * 7]) + ((0 + filter[8]) * orig[i * 8192 + j + 8178 * 8]);
      sol[i * 8192 + j] = result;
    }
  }
}