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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((i + 4) - ((8 - 1) + ((k + 4) - 8)));
        i_col = ((j + 4) - ((8 - 1) + ((k + 4) - 8)));
        j_col = (k + 4) - 8;
        t += ((orig[i_col * 64 + j_col] == 0) ? 0 : 1) * filter[k];
      }
      sol[i * 64 + j] = t;
    }
  }
}