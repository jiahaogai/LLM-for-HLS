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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        if (((i_col >= 0) && (i_col < 256))) {
          
#pragma ACCEL PIPELINE auto{flatten}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          inner_middle:
          for (j_col = -4; j_col < 5; j_col++) {
            k_col = j + j_col;
            if (((k_col >= 0) && (k_col < 256))) {
              t += ((orig[i_col * 256 + k_col] * filter[((k + 4) * 5) + j_col + 4]));
            }
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}