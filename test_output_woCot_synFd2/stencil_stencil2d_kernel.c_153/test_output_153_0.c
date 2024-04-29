#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 9; j++) {
      int tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      inner:
      for (k = 0; k < 8; k++) {
        tmp += orig[i * 8 + k] * filter[j * 8 + k];
      }
      result = tmp;
      sol[i * 9 + j] = result;
    }
  }
}