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
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    inner:
    for (j = 0; j < 256; j++) {
      result = 0;
      middle:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 256 + j + align(k - 4, 16)];
      }
      sol[i * 256 + j] = result;
    }
  }
}