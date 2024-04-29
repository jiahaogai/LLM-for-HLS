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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i - 4 + k_col;
        if ((((k >= 0) && (k < 256))) && ((j >= 0) && (j < 256))) {
          buff[k_col] = orig[k * 256 + j];
        }
      }
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      int k_col_1 = 0;
      int k_col_end = 9;
      int k_col_step = 1;
      while (k_col_1 < k_col_end) {
        
#pragma ACCEL PIPELINE auto{off}
        sum += buff[k_col_1] * filter[k_col_1];
        k_col_1 += k_col_step;
      }
      sol[i * 256 + j] = sum;
    }
  }
}