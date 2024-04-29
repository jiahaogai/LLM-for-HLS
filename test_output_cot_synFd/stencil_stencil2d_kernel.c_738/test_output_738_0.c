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
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 64; j++) {
      result = ((filter[0] * orig[i - 8 + ((j - 8) + 0)]) + (filter[1] * orig[i - 8 + ((j - 8) + 1)]) + (filter[2] * orig[i - 8 + ((j - 8) + 2)]) + (filter[3] * orig[i - 8 + ((j - 8) + 3)]) + (filter[4] * orig[i - 8 + ((j - 8) + 4)]) + (filter[5] * orig[i - 8 + ((j - 8) + 5)]) + (filter[6] * orig[i - 8 + ((j - 8) + 6)]) + (filter[7] * orig[i - 8 + ((j - 8) + 7)]) + (filter[8] * orig[i - 8 + ((j - 8) + 8)]));
      sol[i + j] = result;
    }
  }
}