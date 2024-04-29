#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      tmp += orig[k] * filter[j];
    }
    sol[i] = tmp;
  }
}