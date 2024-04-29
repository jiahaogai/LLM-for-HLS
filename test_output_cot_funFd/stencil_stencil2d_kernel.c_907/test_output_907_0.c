#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 128 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1 - 1; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{64}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (k - 4) / 2 + ((j + (k - 4) / 2) * (64 + 1 - 1))];
      }
      sol[i + (j * (64 + 1 - 1)) - 1] = result;
    }
  }
}