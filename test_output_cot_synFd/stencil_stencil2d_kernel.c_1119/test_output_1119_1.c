#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 8186; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 8; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}