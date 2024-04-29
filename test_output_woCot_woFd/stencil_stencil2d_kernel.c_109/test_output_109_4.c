#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((filter[0] * orig[i - 1 + (j - 1) * 8192]) + (filter[1] * orig[i - 1 + j * 8192]) + (filter[2] * orig[i - 1 + (j + 1) * 8192]) + (filter[3] * orig[i + (j - 1) * 8192]) + (filter[4] * orig[i + j * 8192]) + (filter[5] * orig[i + (j + 1) * 8192]) + (filter[6] * orig[i + 1 + (j - 1) * 8192]) + (filter[7] * orig[i + 1 + j * 8192]) + (filter[8] * orig[i + 1 + (j + 1) * 8192])) >> 12;
      sol[i + j * 8192] = result;
    }
  }
}