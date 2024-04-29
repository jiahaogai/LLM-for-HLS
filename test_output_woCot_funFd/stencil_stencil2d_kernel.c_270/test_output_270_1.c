#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 8));
        i_col = ((16 * k) + 1 + ((k % 8) * 16));
        j_col = ((8 * j) + (k % 8));
        t += filter[k] * orig[k_col * 64 + i_col] * orig[j_col * 64];
      }
      sol[i * 8 + j] = t;
    }
  }
}