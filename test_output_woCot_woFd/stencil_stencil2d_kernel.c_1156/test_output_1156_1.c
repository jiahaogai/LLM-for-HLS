#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 128 - 1; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-1 + k) * 128];
      }
      sol[i * 128 + j] = sum;
    }
  }
}