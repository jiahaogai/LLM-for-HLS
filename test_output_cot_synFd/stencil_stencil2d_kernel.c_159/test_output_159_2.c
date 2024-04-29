#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8191; j++) {
      result = ((filter[0] * orig[i - 1,j - 1]) + (filter[1] * orig[i - 1,j]) + (filter[2] * orig[i - 1,j + 1]) + (filter[3] * orig[i,j - 1]) + (filter[4] * orig[i,j]) + (filter[5] * orig[i,j + 1]) + (filter[6] * orig[i + 1,j - 1]) + (filter[7] * orig[i + 1,j]) + (filter[8] * orig[i + 1,j + 1])) / 81;
      sol[i,j] = result;
    }
  }
}