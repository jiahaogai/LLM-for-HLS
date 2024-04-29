#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 16; i < 8192 - 16; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 16; j < 8192 - 16; j++) {
      result = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + dx[k]][j + dy[k]];
      }
      sol[i][j] = result;
    }
  }
}