#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    int val = ((int )0);
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      t = i - 4 + j;
      if (t < 0) {
        t = 0;
      }
      row = t / 64;
      col = t - row * 64;
      val += ((int )filter[j]) * orig[row * 64 + col];
    }
    sol[i] = val;
  }
}