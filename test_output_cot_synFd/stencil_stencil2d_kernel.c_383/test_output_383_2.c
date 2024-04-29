Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      temp = orig[i * 8192 + j];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        temp -= filter[k] * orig[(i + (-4 + k)) * 8192 + j];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        temp -= filter[k] * orig[i * 8192 + j + (-4 + k)];
      }
      sol[i * 8192 + j] = temp;
    }
  }
}