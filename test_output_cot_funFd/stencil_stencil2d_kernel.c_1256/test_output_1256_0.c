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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 8; j < 8192; j += 8) {
      temp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = i - 4 + k_col;
        k = k_row * 8192 + j - 4;
        temp += filter[k_col] * orig[k];
      }
      sol[j] = temp;
    }
  }
}