#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 33; j++) {
      temp = orig[i * 32 + j] + filter[0] * orig[i * 32 + j - 1] + filter[1] * orig[i * 32 + j - 2] + filter[2] * orig[i * 32 + j - 3] + filter[3] * orig[i * 32 + j + 1] + filter[4] * orig[i * 32 + j + 2] + filter[5] * orig[i * 32 + j + 3] + filter[6] * orig[i * 32 + j - 8] + filter[7] * orig[i * 32 + j - 7] + filter[8] * orig[i * 32 + j - 6] + filter[9] * orig[i * 32 + j - 5];
      sol[i * 32 + j] = temp;
    }
  }
}