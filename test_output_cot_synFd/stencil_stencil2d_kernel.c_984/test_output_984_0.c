#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (0 * orig[i + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192]) + (1 * orig[i - 1 + j * 8192]) + (2 * orig[i + j * 8192]) + (1 * orig[i + 1 + j * 8192]) + (0 * orig[i - 1 + (j + 1) * 8192]) + (0 * orig[i + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192]));
      sol[i + j * 8192] = result;
    }
  }
}