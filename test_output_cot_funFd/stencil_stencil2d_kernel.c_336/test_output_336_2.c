#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8176; j++) {
      result = ((0 * orig[i - 1,j]) + (1 * orig[i,j]) + (0 * orig[i + 1,j])) + ((0 * orig[i - 1,j + 1]) + (2 * orig[i,j + 1]) + (0 * orig[i + 1,j + 1])) + ((0 * orig[i - 1,j - 1]) + (1 * orig[i,j - 1]) + (0 * orig[i + 1,j - 1]));
      sol[i,j] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      orig[i,j] = sol[i,j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      result = 0;
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-1 + k),j];
      }
      sol[i,j] = result;
    }
  }
}