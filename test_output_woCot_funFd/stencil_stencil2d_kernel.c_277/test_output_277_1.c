Code: 
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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        
#pragma ACCEL PARALLEL reduction=k_col FACTOR=auto{1}
        inner_1:
        for (k_col = -4; k_col < 5; k_col++) {
          i_col = i + k;
          j_col = j + k_col;
          if ((((i_col >= 0) && (i_col < 256)) && ((j_col >= 0) && (j_col < 256)))) {
            t += ((orig[i_col * 256 + j_col] * filter[k + 4]) * filter[k_col + 4]);
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}