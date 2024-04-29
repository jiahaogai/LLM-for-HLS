#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_filter[81];
  int flatten_orig[8192];
  int flatten_sol[8192];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  // Flatten filter and orig
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i_col = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (i_col < 9) {
    int _in_i_col = i_col;
    flatten_filter[i_col] = filter[i_col];
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    j_col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (j_col < 9) {
      int _in_j_col = j_col;
      flatten_filter[i_col + 9 * j_col] = filter[j_col];
      
#pragma ACCEL PARALLEL reduction=flatten_sol FACTOR=auto{1}
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=flatten_sol FACTOR=auto{16}
      while (k_col < 9) {
        int _in_k_col = k_col;
        int _in_i = _in_i_col + 1 - 4;
        int _in_j = _in_j_col + 1 - 4;
        int _in_k = _in_k_col + 1 - 4;
        i = _in_i;
        j = _in_j;
        k = _in_k;
        flatten_orig[i_col + 9 * j_col + 81 * k_col] = orig[i * 9 + j + 81 * k];
        
#pragma ACCEL PIPELINE auto{off}
        flatten_sol[i_col + 9 * j_col + 81 * k_col] = 0;
        k_col++;
      }
      j_col++;
    }
    i_col++;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i_col = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  while (i_col < 9) {
    int _in_i_col = i_col;
    
#pragma ACCEL PIPELINE auto{off}
    j_col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (j_col < 9) {
      int _in_j_col = j_col;
      
#pragma ACCEL PIPELINE auto{off}
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=flatten_sol FACTOR=auto{1}
      while (k_col < 9) {
        int _in_k_col = k_col;
        int _in_i = _in_i_col + 4 - 1;
        int _in_j = _in_j_col + 4 - 1;
        int _in_k = _in_k_col + 4 - 1;
        i = _in_i;
        j = _in_j;
        k = _in_k;
        sol[i_col + 9 * j_col + 81 * k_col] = ((((flatten_filter[0 + 9 * 0 + 81 * 0] * flatten_orig[i_col + 9 * 0 + 81 * 0]) + (flatten_filter[0 + 9 * 1 + 81 * 0] * flatten_orig[i_col + 9 * 1 + 81 * 0])) + (flatten_filter[0 + 9 * 2 + 81 * 0] * flatten_orig[i_col + 9 * 2 + 81 * 0])) + (flatten_filter[0 + 9 * 3 + 81 * 0] * flatten_orig[i_col + 9 * 3 + 81 * 0])) + ((((flatten_filter[1 + 9 * 0 + 81 * 0] * flatten_orig[i_col + 9 * 0 + 81 * 1]) + (flatten_filter[1 + 9 * 1 + 81 * 0] * flatten_orig[i_col + 9 * 1 + 81 * 1])) + (flatten_filter[1 + 9 * 2 + 81 * 0] * flatten_orig[i_col + 9 * 2 + 81 * 1])) + (flatten_filter[1 + 9 * 3 + 81 * 0] * flatten_orig[i_col + 9 * 3 + 81 * 1])) + ((((flatten_filter[2 + 9 * 0 + 81 * 0] * flatten_orig[i_col + 9 * 0 + 81 * 2]) + (flatten_filter[2 + 9 * 1 + 81 * 0] * flatten_orig[i_col + 9 * 1 + 81 * 2])) + (flatten_filter[2 + 9 * 2 + 81 * 0] * flatten_orig[i_col + 9 * 2 + 81 * 2])) + (flatten_filter[2 + 9 * 3 + 81 * 0] * flatten_orig[i_col + 9 * 3 + 81 * 2])) + ((((flatten_filter[3 + 9 * 0 + 81 * 0] * flatten_orig[i_col + 9 * 0 + 81 * 3]) + (flatten_filter[3 + 9 * 1 + 81 * 0] * flatten_orig[i_col + 9 * 1 + 81 * 3])) + (flatten_filter[3 + 9 * 2 + 81 * 0] * flatten_orig[i_col + 9 * 2 + 81 * 3])) + (flatten_filter[3 + 9 * 3 + 81 * 0] * flatten_orig[i_col + 9 * 3 + 81 * 3]));
        k_col++;
      }
      j_col++;
    }
    i_col++;
  }
}