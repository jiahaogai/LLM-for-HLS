#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8188; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        result += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = result;
    }
  }
}