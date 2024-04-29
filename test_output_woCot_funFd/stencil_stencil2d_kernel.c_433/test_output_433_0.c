#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
<<<<<<< HEAD
  int i_col;
  int j_col;
  int flit;
=======
  int row;
  int col;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loopj_col:
/* Standardize from: for(j_col = 0;j_col < 9;j_col++) {...} */
  for (j_col = 0; j_col <= 8; j_col++) {
    int _in_j_col = 0 + 8L * j_col;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi_col:
/* Standardize from: for(i_col = 0;i_col < 9;i_col++) {...} */
    for (i_col = 0; i_col <= 8; i_col++) {
      int _in_i_col = (_in_j_col + 0) + 8L * i_col;
      flit = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:
/* Standardize from: for(k = 8;k > 0;k--) {...} */
      for (k = 7; k >= 0; k--) {
        int _in_k = 8L + 8L * k;
        int _in_idx = _in_k * 8 + _in_i_col;
        flit = orig[_in_idx] * filter[k + 8] + flit;
      }
      sol[_in_i_col] = flit;
=======
  
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}