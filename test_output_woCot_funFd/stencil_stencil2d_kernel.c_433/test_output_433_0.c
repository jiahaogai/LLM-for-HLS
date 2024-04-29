#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loop_row:
  for (row = 0; row < 64; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_col:
    for (col = 0; col < 64; col++) {
      val = 0;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row + (-4 + k_col);
        j = col + (-4 + k);
        val += orig[i * 64 + j] * filter[k_col * 9 + k];
        k_col++;
      }
      sol[row * 64 + col] = val;
    }
  }
}