#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 8192; i++) {
     middle:
    for (j = 0; j < 8192; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + kernel_offsets[k].i]
                                     [j + kernel_offsets[k].j];
      }
      sol[i][j] = result;
      result = 0;
    }
  }
}