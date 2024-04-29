#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        int k_row = 4 + (-1 + k_col);
        int k = idx + k_row * 256 + k_col;
        sum += orig[k] * filter[k_col];
      }
      sol[idx] = sum;
      idx++;
    }
  }
}