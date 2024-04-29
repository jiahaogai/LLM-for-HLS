#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 256;
      sol_row = i * 256;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 256; k++) {
        orig_col = k * 256;
        sol_col = k * 256;
        j_col = j * 256;
        i_col = i * 256;
        k_col = k * 256;
        sol[sol_col + j] = ((filter[0] * orig[orig_col + j_col + i]) + (filter[1] * orig[orig_col + j_col + i + 1]) + (filter[2] * orig[orig_col + j_col + i + 2]) + (filter[3] * orig[orig_col + j_col + i + 256]) + (filter[4] * orig[orig_col + j_col + i + 257]) + (filter[5] * orig[orig_col + j_col + i + 258]) + (filter[6] * orig[orig_col + j_col + i + 512]) + (filter[7] * orig[orig_col + j_col + i + 513]) + (filter[8] * orig[orig_col + j_col + i + 514])) / 256;
      }
    }
  }
}