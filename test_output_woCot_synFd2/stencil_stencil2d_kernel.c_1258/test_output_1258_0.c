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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 8));
        i_col = ((8 * j) + (k % 8));
        buf += ((orig[k_col * 256 + i_col] - 128) * filter[k]);
      }
      sol[i * 256 + j] = (buf + 128);
    }
  }
}