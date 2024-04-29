#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1][j - 1]) + (1 * orig[i - 1][j]) + (0 * orig[i - 1][j + 1]) + (0 * orig[i][j - 1]) + (1 * orig[i][j]) + (0 * orig[i][j + 1]) + (0 * orig[i + 1][j - 1]) + (1 * orig[i + 1][j]) + (0 * orig[i + 1][j + 1])) + filter[4];
      sol[i][j] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      orig[i][j] = sol[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1][j - 1]) + (1 * orig[i - 1][j]) + (0 * orig[i - 1][j + 1]) + (0 * orig[i][j - 1]) + (1 * orig[i][j]) + (0 * orig[i][j + 1]) + (0 * orig[i + 1][j - 1]) + (1 * orig[i + 1][j]) + (0 * orig[i + 1][j + 1])) + filter[4];
      sol[i][j] = result;
    }
  }
}