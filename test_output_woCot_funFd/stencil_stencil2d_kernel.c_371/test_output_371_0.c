#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = -4; k <= 4; k++) {
        result += filter[k + 4] * orig[i + k * 64 + 8160];
      }
      sol[i * 64 + j] = result;
    }
  }
}