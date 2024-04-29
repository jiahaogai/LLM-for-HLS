#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = i + (-4 + k_col);
        if ((((i < 4) || (i > 71)) || (k_row < 0)) || (k_row > 71)) {
          k = 0;
        }
        
#if defined(_OPENMP)
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
          col:
          for (k_row = (8 * (i / 8)); k_row < (8 * (1 + (i / 8))); k_row++) {
            if ((k_row == k_row)) {
              k = ((64 * k_row) + j);
            }
            sum += filter[k_col] * orig[k];
          }
        
#endif
      }
      sol[((64 * i) + j)] = sum;
    }
  }
}