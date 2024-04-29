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
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 32; j++) {
      result = ((filter[0] * orig[i * 32 + j]) + (filter[1] * orig[(i - 1) * 32 + j]) + (filter[2] * orig[(i - 2) * 32 + j]) + (filter[3] * orig[i * 32 + j - 1]) + (filter[4] * orig[i * 32 + j + 1]) + (filter[5] * orig[(i + 2) * 32 + j]) + (filter[6] * orig[(i + 1) * 32 + j]) + (filter[7] * orig[(i - 1) * 32 + j - 1]) + (filter[8] * orig[(i - 1) * 32 + j + 1]));
      sol[i * 32 + j] = result;
    }
  }
}