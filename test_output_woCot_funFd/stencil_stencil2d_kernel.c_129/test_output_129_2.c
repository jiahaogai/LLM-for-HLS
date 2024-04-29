#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t;
  int fs = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
    inner:
    for (k = 0; k < 9; k++) {
      t = orig[fs + ((k - 4) * 64)];
      tmp += filter[k] * t;
    }
    sol[i] = tmp;
    fs++;
  }
}