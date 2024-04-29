#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long h;
  long pad_size;
  long orig_row_idx;
  long orig_col_idx;
  long orig_pad_idx;
  long sol_row_idx;
  long sol_col_idx;
  long d;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_size = 1;
  bound = (C0 + 2 * pad_size) * (C1 + 2 * pad_size) * (C1 + 2 * pad_size);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_size = 1;
  h = C0 + 2 * pad_size;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_j:
  for (j = 0; j < h; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_k:
    for (k = 0; k < h; k++) {
      loop_i:
      for (i = 0; i < h; i++) {
        i_col = pad_size + i;
        j_col = pad_size + j;
        k_col = pad_size + k;
        orig_row_idx = k_col * (C1 + 2 * pad_size) * (C0 + 2 * pad_size) + j_col * (C0 + 2 * pad_size) + i_col;
        sol_row_idx = k * (C1 + 2 * pad_size) * (C0 + 2 * pad_size) + j * (C0 + 2 * pad_size) + i;
        loop_d:
        for (d = 0; d < 32; d++) {
          orig_pad_idx = orig_row_idx * 32 + d;
          sol[sol_row_idx * 32 + d] = ((long )0);
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{16}
          loop_k_col:
          for (k_col = 0; k_col < 39; k_col++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            
#pragma ACCEL PARALLEL FACTOR=auto{1}
            loop_j_col:
            for (j_col = 0; j_col < 39; j_col++) {
              orig_col_idx = k_col * (C1 + 2 * pad_size) * (C0 + 2 * pad_size) + j_col * (C0 + 2 * pad_size) + i_col;
              sol[sol_row_idx * 32 + d] += orig[orig_col_idx * 32 + d] * 1L;
            }
          }
        }
      }
    }
  }
}