Code: 
 #include <math.h>
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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((k / 3) * 256) + i;
        i_col = ((k % 3) * 256) + i;
        j_col = ((k_col - i_col) + j);
        t += filter[k] * orig[j_col];
      }
      sol[j] = t;
    }
    for (j = 0; j < 256; j++) {
      orig[j] = sol[j];
    }
  }
}