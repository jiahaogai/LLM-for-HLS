#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
     middle:
    for (j = 1; j < 8191; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-1 + k) * 8191 + j];
      }
      sol[i * 8191 + j] = result;
    }
  }
}