Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32 + 2 * 1; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i * (32 + 2 * 1) + j + pad - 1 + k * (32 + 2 * 1)];
      }
      sol[i * (32 + 2 * 1) + j] = sum;
    }
  }
}