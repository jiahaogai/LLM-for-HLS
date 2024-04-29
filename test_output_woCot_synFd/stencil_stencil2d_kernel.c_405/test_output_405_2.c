#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        buf[k_col] = orig[((i + (-4 + k_col))) * 256 + j];
      }
      sol[i * 256 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (k = 0; k < 9; k++) {
        sol[i * 256 + j] += filter[k] * buf[k];
      }
    }
  }
}