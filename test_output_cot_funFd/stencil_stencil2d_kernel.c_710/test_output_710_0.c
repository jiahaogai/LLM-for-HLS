#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 32 + 1 - 1; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 32]) + (1 * orig[i + (j - 1) * 32]) + (2 * orig[i + 1 + (j - 1) * 32]) + (3 * orig[i - 1 + j * 32]) + (4 * orig[i + j * 32]) + (5 * orig[i + 1 + j * 32]) + (6 * orig[i - 1 + (j + 1) * 32]) + (7 * orig[i + (j + 1) * 32]) + (8 * orig[i + 1 + (j + 1) * 32])) / 36;
      sol[i + j * 32] = result;
    }
  }
}