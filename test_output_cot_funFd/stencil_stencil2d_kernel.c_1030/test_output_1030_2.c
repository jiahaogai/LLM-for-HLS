#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 32 + 2 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 32 + 2 * 1; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int k_row = i - 1 + k - 4;
        int k_col = j - 1 + pad;
        if (k_row < 0 || k_row > 31 - 1 || k_col < 0 || k_col > 31 - 1) {
          sum += 0;
        }
         else {
          sum += orig[k_row * 32 + k_col] * filter[k];
        }
      }
      sol[i * 32 + j] = sum;
    }
  }
}