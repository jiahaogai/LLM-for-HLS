#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      result = ((filter[0] * orig[i - 1 + (-1) * 8192]) + (filter[1] * orig[i - 1 + 0 * 8192]) + (filter[2] * orig[i - 1 + 1 * 8192])) + ((filter[3] * orig[i + (-1) * 8192]) + (filter[4] * orig[i + 0 * 8192]) + (filter[5] * orig[i + 1 * 8192])) + ((filter[6] * orig[i + 1 + (-1) * 8192]) + (filter[7] * orig[i + 1 + 0 * 8192]) + (filter[8] * orig[i + 1 + 1 * 8192]));
      sol[i * 8192 + j] = result;
    }
  }
}