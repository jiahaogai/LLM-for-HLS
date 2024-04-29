#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
    inner:
    for (j = 0; j < 8; j++) {
      row = i - 4 + j;
      s1:
      for (k = 0; k < 8; k++) {
        col = k - 4;
        t = row * 64 + col;
        sol[i] += filter[j * 8 + k] * orig[t];
      }
    }
  }
}