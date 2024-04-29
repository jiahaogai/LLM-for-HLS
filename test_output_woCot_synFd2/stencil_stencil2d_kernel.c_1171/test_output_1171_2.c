#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + ((k - 4) * 8191)];
      }
      sol[j] = sum;
    }
    sol[8191] = sum;
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 8190; j > 0; j--) {
      sum -= orig[i - 1 + (-1 * (j + 4)) * 8191] * filter[0];
      sol[j] = sum;
    }
    sol[0] = sum;
  }
}