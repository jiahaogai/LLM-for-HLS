#
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((orig[i - 1]) + (orig[i + 1]) + (orig[j - 1]) + (orig[j + 1]) + (orig[j * 8192 + 8191]) + (orig[j * 8192 + 0]) + (orig[j * 8192 + 8190]) + (orig[j * 8192 + 1])) * filter[4] + (orig[i - 1 + (j - 1) * 8192]) * filter[0] + (orig[i - 1 + (j + 1) * 8192]) * filter[2] + (orig[i + 1 + (j - 1) * 8192]) * filter[1] + (orig[i + 1 + (j + 1) * 8192]) * filter[3];
      sol[j * 8192 + i] = result;
    }
  }
}