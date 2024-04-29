#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{stencil_label1}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (8192 - 2 * 1)) * filter[0]) + ((8192 - 2 * 1) * (filter[1])) + ((8192 - 2 * 1) * (filter[2])) + ((8192 - 2 * 1) * (filter[3])) + ((8192 - 2 * 1) * (filter[4])) + ((8192 - 2 * 1) * (filter[5])) + ((8192 - 2 * 1) * (filter[6])) + ((8192 - 2 * 1) * (filter[7])) + ((8192 - 2 * 1) * (filter[8]));
      result -= ((8192 * (1 - 2 * 1)) * (orig[i - 1 + (8192 * (j - 1))])) + ((8192 - 2 * 1) * (1 - 2 * 1) * (orig[i + (8192 * (j - 1))])) + ((8192 - 2 * 1) * (orig[i + (8192 * (j + 1))])) + ((8192 * (1 - 2 * 1)) * (orig[i - 1 + (8192 * (j + 1))]));
      sol[i + (8192 * j)] = result;
    }
  }
}