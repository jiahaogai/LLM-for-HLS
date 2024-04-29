#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  int idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = ((((64 + 2) * (128 + 2)) * k) + (((64 + 2) * j) + i)) + 2560;
        result += orig[idx] * filter[k];
      }
      sol[((64 * i) + j)] = result;
    }
  }
}