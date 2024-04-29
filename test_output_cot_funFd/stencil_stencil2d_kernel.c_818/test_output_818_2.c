#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (1 * orig[i + (j - 1) * 8192]) + (2 * orig[i + 1 + (j - 1) * 8192]) + (3 * orig[i - 1 + j * 8192]) + (4 * orig[i + j * 8192]) + (5 * orig[i + 1 + j * 8192]) + (6 * orig[i - 1 + (j + 1) * 8192]) + (7 * orig[i + (j + 1) * 8192]) + (8 * orig[i + 1 + (j + 1) * 8192])) / 4;
      sol[i + j * 8192] = result;
    }
  }
}