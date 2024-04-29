#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        sum += orig[i + ((k - 4) * 8191)] * filter[k];
      }
      sol[j] = sum;
    }
    sol[8192 - 1] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8192 - 10; j < 8192 - 1; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 1; k < 9; k++) {
        sum += orig[i + ((k - 4) * 8191)] * filter[k];
      }
      sol[j] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += sol[j + ((k - 4) * 8191)] * filter[k];
      }
      orig[j] = sum;
    }
    orig[8192 - 1] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8192 - 9; j < 8192 - 1; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += sol[j + ((k - 4) * 8191)] * filter[k];
      }
      orig[j] = sum;
    }
  }
}