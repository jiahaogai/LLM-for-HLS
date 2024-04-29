#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = orig[i * 8 + j] * filter[k] + 
                 orig[i * 8 + k] * filter[j] + 
                 orig[i * 8 + (7 - k)] * filter[7 - j] + 
                 orig[((i + 1) * 8) - 1 - j] * filter[8 - k];
        sol[i * 8 + j] = result;
      }
    }
  }
}