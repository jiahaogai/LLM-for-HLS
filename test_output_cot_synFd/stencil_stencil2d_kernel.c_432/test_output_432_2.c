#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 9; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += orig[i * 9 + k] * filter[j * 9 + k];
      }
    }
    sol[i] = result;
    result = 0;
  }
}