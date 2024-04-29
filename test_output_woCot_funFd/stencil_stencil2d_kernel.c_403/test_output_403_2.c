#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) > 0 ? (k - 4) : 0)][j + ((k - 4) > 0 ? (k - 4) : 0)];
      }
      sol[i][j] = result;
    }
  }
}