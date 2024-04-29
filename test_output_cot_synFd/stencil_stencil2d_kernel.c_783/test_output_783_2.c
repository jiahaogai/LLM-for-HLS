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
  int bound;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (row = 0; row < 64; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 0; col < 64; col++) {
      bound = ((row > 0) ? 1 : 0) + ((row < 63) ? 1 : 0) + ((col > 0) ? 1 : 0) + ((col < 63) ? 1 : 0);
      flit_i = 0;
      
#pragma ACCEL PARALLEL reduction = flit_i FACTOR=auto{2}
      loop_k_col:
      for (k_col = (col > 0 ? -1 : 0); k_col <= (col < 63 ? 1 : 0); k_col += ((col > 0) ? -1 : 1)) {
        flit_j = 0;
        
#pragma ACCEL PARALLEL reduction = flit_j FACTOR=auto{2}
        loop_k:
        for (k = (row > 0 ? -1 : 0); k <= (row < 63 ? 1 : 0); k += ((row > 0) ? -1 : 1)) {
          i = row + k;
          j = col + k_col;
          flit_j += filter[k_col + 1] * orig[i * 64 + j];
        }
        flit_i += flit_j;
      }
      sol[row * 64 + col] = flit_i / bound;
    }
  }
}