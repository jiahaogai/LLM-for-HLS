#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int t;
  col = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0; j < 32; j++) {
    row = j * 32;
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      int sum = 0;
      int k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        int i_k = row + k / 32;
        int j_k = col + k % 32;
        sum += orig[i_k * 32 + j_k] * filter[k];
      }
      sol[row * 32 + col] = sum;
    }
    col = 1;
  }
}