#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 64; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 64 + j + ((k - 4) * 64)];
      }
      sol[i * 64 + j] = result;
    }
  }
}