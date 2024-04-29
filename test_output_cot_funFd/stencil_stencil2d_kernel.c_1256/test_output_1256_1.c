#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int offset;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    temp = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{9}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i - 4 + j % 5;
      k_row = i - 4 + j / 5;
      if (k_col < 0 || k_col > 8191) {
        k = 0;
      }
       else if (k_row < 0 || k_row > 8191) {
        k = 0;
      }
       else {
        k = k_row * 8192 + k_col;
      }
      temp += filter[j] * orig[k];
    }
    sol[i] = temp;
  }
}