#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      idx = (8192 * (i - 1)) + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[(8192 * (i - 1 + ((k - center) > 0 ? 1 : 0))) + j - 1 + ((k - center) > 0 ? 1 : 0)];
      }
    }
  }
}