#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 128 - 1; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) * 64)];
      }
      sol[j + ((i - 4) * 128)] = result;
    }
  }
}