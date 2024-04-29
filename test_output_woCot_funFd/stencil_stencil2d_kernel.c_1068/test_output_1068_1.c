Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 64; j++) {
      buf = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + (4 - 2 + (k % 3));
        buf += filter[k] * orig[k_col * 64 + j + (4 - 2 + (k / 3))];
      }
      sol[i * 64 + j] = buf;
    }
  }
}