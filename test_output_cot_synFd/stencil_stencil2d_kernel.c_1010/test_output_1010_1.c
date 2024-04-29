Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + ((k / 3) - 1) + ((j + ((k % 3) - 1)) * 33)];
      }
      sol[i + j * 33] = sum;
    }
  }
}