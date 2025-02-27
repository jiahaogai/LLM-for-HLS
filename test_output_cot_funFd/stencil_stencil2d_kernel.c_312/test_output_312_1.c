#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 9; j++) {
      int tmp_outer = i - 4;
      int tmp_inner = j - 4;
      int tmp = filter[j] * orig[tmp_outer * 64 + tmp_inner];
      result = result + tmp;
    }
    sol[i] = result;
    result = 0;
  }
}