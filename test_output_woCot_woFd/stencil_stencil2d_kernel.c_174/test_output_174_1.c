#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
     middle:
    for (j = 0; j < 8192; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}