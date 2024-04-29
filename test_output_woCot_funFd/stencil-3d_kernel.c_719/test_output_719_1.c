#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idxP;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = (40 * 1) + 1;
     j_col = (1 * 40) + 1;
     i_col = 1;
     k_row = (40 * (k - 1)) + 1;
     j_row = (1 * (1 - 1)) + 1;
     i_row = 1 - 1;
     loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        idx = i_row * k_col + j_row * j_col + k_row * i_col;
        idxP = idx - 1;
        sum = orig[idxP] + orig[idxP + 1] + orig[idxP + k_col] + orig[idxP + k_col + 1] + orig[idx + k_col] + orig[idx + k_col + 1] + orig[idx + 1] + orig[idx + 1 + k_col];
        sol[idx] = sum;
      }
      i_row++;
    }
    j_row++;
  }
  k_row++;
}