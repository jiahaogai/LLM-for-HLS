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
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        i_row = i - 1;
        j_row = j - 1;
        k_row = k - 1;
        i_col = i + 1;
        j_col = j + 1;
        k_col = k + 1;
        if (i_col > 32) {
          i_col = 32;
        }
        if (j_col > 32) {
          j_col = 32;
        }
        if (k_col > 32) {
          k_col = 32;
        }
        idx = i + j * (32 + 1) + k * ((32 + 1) * (32 + 1));
        idx_col = i_col + j_col * (32 + 1) + k_col * ((32 + 1) * (32 + 1));
        sol[idx] = ((orig[idx_col] - ((((k_col * (1L + 0L)) + (j_col * (0L + 1L))) + (i_col * (0L + 0L)))) / (1L * 1L * 1L)) + ((orig[idx] - ((((k_row * (0L + 1L)) + (j_row * (1L + 0L))) + (i_row * (1L + 1L)))) / (2L * 2L * 2L))) + ((orig[idx_col + (32 + 1) * ((32 + 1) * (32 + 1))]) - ((((k_col * (0L + 1L)) + (j_col * (1L + 0L))) + (i_col * (1L + 1L)))) / (1L * 2L * 2L)));
      }
    }
  }
}