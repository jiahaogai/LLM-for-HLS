Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buff[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      buff[j] = orig[i - 4 + j];
    }
    inner:
    for (j = 0; j < 9; j++) {
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      inner_par:
      for (k = 0; k < 9; k++) {
        sol[i] += buff[k] * filter[k_col++];
      }
    }
  }
}