- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Divide the loop into parallelize into 16 different instances to exploit the parallelism.

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
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (i - 1)) + (j - 1)) * 2;
      sol[result] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[result] += filter[k] * orig[(8192 * (i + (-1 + k))) + (j + (-1 + k))];
      }
    }
  }
}