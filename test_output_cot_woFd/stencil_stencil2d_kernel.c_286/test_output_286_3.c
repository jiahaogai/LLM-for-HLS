#pragma ACCEL kernel

void stencil(char orig[8192],char sol[8192],char filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      buf = 0;
      inner:
      for (k = 0; k < 9; k++) {
        i_col = i - 4 + k / 5;
        k_col = j - 4 + k % 5;
        buf += ((int )filter[k]) * orig[i_col * 256 + k_col];
      }
      sol[i * 256 + j] = buf;
    }
  }
}