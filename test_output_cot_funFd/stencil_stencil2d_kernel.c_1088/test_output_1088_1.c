#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flit_i;
  int flit_j;
  int pad;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  pad = 1;
  flit_i = 9 + 2 * pad;
  flit_j = 9 + 2 * pad;
  row = 8;
  col = 8;
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      int sum = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = pad + j + ((k + pad) * 8);
        int orig_idx = i * 64 + k_col;
        sum += orig[orig_idx] * filter[k];
      }
      int sol_idx = (i + pad) * 8 + j + pad;
      sol[sol_idx] = sum;
    }
  }
}