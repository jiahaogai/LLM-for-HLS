#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 33; j++) {
      result = ((filter[0] * orig[i - 1 + (j - 1) * 32]) + (filter[1] * orig[i - 1 + j * 32]) + (filter[2] * orig[i - 1 + (j + 1) * 32]) + (filter[3] * orig[i + (j - 1) * 32]) + (filter[4] * orig[i + j * 32]) + (filter[5] * orig[i + (j + 1) * 32]) + (filter[6] * orig[i + 1 + (j - 1) * 32]) + (filter[7] * orig[i + 1 + j * 32]) + (filter[8] * orig[i + 1 + (j + 1) * 32])) / 81;
      sol[i + j * 32] = result;
    }
  }
}