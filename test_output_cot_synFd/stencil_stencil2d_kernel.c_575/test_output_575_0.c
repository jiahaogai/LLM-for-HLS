#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      elem = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_row = -4; k_row <= 4; k_row++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_col = -4; k_col <= 4; k_col++) {
          k = (k_row + 4) * 8 + k_col + 4;
          elem += filter[k] * orig[i * 8 + k_row + 2] * orig[j * 8 + k_col + 2];
        }
      }
      sol[i * 8 + 2 + 4] = elem;
    }
  }
}