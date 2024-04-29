#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + j;
      if (((x >= 0) && (x < 8192))) {
        t += ((orig[x]) * (filter[j]));
      }
    }
    sol[i] = t;
  }
}