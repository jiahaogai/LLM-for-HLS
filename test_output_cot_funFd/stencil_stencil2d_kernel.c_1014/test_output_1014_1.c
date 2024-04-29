#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (0 * orig[i - 0 + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192])) + ((0 * orig[i - 1 + (j - 0) * 8192]) + (1 * orig[i - 0 + (j - 0) * 8192]) + (0 * orig[i + 1 + (j - 0) * 8192])) + ((0 * orig[i - 1 + (j + 1) * 8192]) + (0 * orig[i - 0 + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192]));
      sol[i + j * 8192] = result;
    }
  }
}