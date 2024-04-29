#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8176; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (0 * orig[i + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192]) + (1 * orig[i - 1 + j * 8192]) + (2 * orig[i + j * 8192]) + (1 * orig[i + 1 + j * 8192]) + (0 * orig[i - 1 + (j + 1) * 8192]) + (0 * orig[i + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192])) / 256;
      sol[i + j * 8192] = result;
    }
  }
}