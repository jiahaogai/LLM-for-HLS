Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      temp = 0;
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = k_col;
        if ((((i + k_row) >= 0) && ((i + k_row) < 128))) {
          if ((((j + k_col) >= 0) && ((j + k_col) < 64))) {
            k = (i + k_row) * 64 + (j + k_col);
            temp += orig[k] * filter[k_col];
          }
        }
      }
      sol[i * 64 + j] = temp;
    }
  }
}