#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
     k_col = k;
     i_col = 32 + 1;
     j_col = k_col;
     k_row = 32 + 1 - 32;
     i_row = k;
     j_row = i_row;
     loop_j:
     for (j = 32 + 1 - 32; j > 0; j--) {
        idx_col = k_col * (32 + 1) * (32 + 1) + i_col * (32 + 1) + j_col;
        idx_row = k_row * (32 + 1) * (32 + 1) + i_row * (32 + 1) + j_row;
        t = C0 * (orig[idx_row] + orig[idx_row + 1] + orig[idx_row + (32 + 1)] + orig[idx_row + (32 + 1) * 2]) +
            C1 * (orig[idx_col] + orig[idx_col + 1] + orig[idx_col + (32 + 1)] + orig[idx_col + (32 + 1) * 2]);
        sol[idx_row] = t;
        j_row--;
     }
     i_row--;
     j_row = j_col + 32 - 1;
     loop_i:
     for (i = 32 + 1 - 32; i > 0; i--) {
        idx_row = k_row * (32 + 1) * (32 + 1) + i_row * (32 + 1) + j_row;
        t = C0 * (sol[idx_row] + sol[idx_row + 1] + sol[idx_row + (32 + 1) ] + sol[idx_row + (32 + 1) * 2]) +
            C1 * (orig[idx_row] + orig[idx_row + 1] + orig[idx_row + (32 + 1)] + orig[idx_row + (32 + 1) * 2]);
        sol[idx_row] = t;
        i_row--;
        j_row -= 2;
     }
     k_col--;
     i_col = i_col - 32 + 1;
     j_col = 1;
   }
}