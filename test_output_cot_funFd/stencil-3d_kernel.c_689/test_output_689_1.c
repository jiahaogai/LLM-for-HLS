#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

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
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 1; k < 40; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 40; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 40; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx = i + (40 * (j + (40 * k)));
        idx_col = i_col + (40 * (j_col + (40 * k_col)));
        t = ((C0 * orig[idx_col]) + (C1 * (((orig[idx_col + 1]) + (orig[idx_col - 1])) + ((orig[idx_col + 40]) + (orig[idx_col - 40]))))) + ((-2) * (((orig[idx_col + 41]) + (orig[idx_col - 39])) + ((orig[idx_col + 39]) + (orig[idx_col - 41]))));
        sol[idx] = t;
      }
    }
  }
}