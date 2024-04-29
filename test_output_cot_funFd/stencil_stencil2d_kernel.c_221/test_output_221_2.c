#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8188; j++) {
      result = ((81 * (orig[i * 8192 + j] - orig[i * 8192 + j - 81])) + (81 * (orig[i * 8192 + j + 81] - orig[i * 8192 + j]))) + (7 * (orig[i * 8192 + j - 1] - orig[i * 8192 + j + 1])) + (orig[i * 8192 + j] - orig[i * 8192 + j - 1]) - (orig[i * 8192 + j] - orig[i * 8192 + j + 1]);
      sol[i * 8192 + j] = result;
    }
  }
//#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8188; j++) {
      orig[i * 8192 + j] = sol[i * 8192 + j];
    }
  }
}