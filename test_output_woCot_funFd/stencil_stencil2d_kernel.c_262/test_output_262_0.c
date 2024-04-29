#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i * 8192 + j] + orig[i * 8192 + j + 1] + orig[i * 8192 + j + 8192] + orig[i * 8192 + j + 8191] + orig[(i + 1) * 8192 + j] + orig[(i + 1) * 8192 + j + 1] + orig[(i + 1) * 8192 + j + 8192] + orig[(i + 1) * 8192 + j + 8191]) / 8);
      sol[i * 8192 + j] = result;
    }
  }
}