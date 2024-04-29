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
    for (j = 8; j < 8184; j += 8) {
      result = ((filter[0] * orig[i + j - 8]) + (filter[1] * orig[i + j - 7]) + (filter[2] * orig[i + j - 6]) + (filter[3] * orig[i + j - 5]) + (filter[4] * orig[i + j - 4]) + (filter[5] * orig[i + j - 3]) + (filter[6] * orig[i + j - 2]) + (filter[7] * orig[i + j - 1]) + (filter[8] * orig[i + j]));
      sol[i + j] = result;
    }
  }
}