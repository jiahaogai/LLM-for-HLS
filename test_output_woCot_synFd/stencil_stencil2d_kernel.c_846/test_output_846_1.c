#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-4 + k) * 8192 + j];
      }
      sol[i * 8192 + j] = result;
    }
  }
}