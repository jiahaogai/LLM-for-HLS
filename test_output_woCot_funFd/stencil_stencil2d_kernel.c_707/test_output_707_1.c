#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (i - 1)) + (j - 1)) * 4;
      k = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 9) {
        sol[result + ((k - 1) * 4)] = filter[k] * orig[result + ((k - 1) * 4)] + ((filter[k] != 0) ? ((4 - filter[k]) * sol[result + ((k - 1) * 4)]) : sol[result + ((k - 1) * 4)]);
        k++;
      }
    }
  }
}