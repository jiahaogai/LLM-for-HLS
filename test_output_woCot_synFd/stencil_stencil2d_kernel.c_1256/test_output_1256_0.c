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
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      temp = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        k_col = j + (-4 + k);
        k_row = i + (-4 + k);
        if (k_col < 1 || k_col > 8191) {
          k_col = 1;
        }
        if (k_row < 1 || k_row > 8191) {
          k_row = 1;
        }
        temp += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = temp;
    }
  }
}