#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
    inner:
    for (k = 0; k < 9; k++) {
      j = i - 4 + k;
      tmp += orig[j] * filter[k];
    }
    sol[i] = tmp;
  }
}