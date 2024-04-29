#pragma ACCEL kernel

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
  long k_pad;
  long j_pad;
  long i_pad;
  long idx;
  long idx_col;
  long idx_row;
  long idx_pad;
  long range_pad;
  long range_col;
  long range_row;
  long count;
  long sum;
  long C0_pad;
  long C1_pad;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  C0_pad = C0 + 2;
  C1_pad = C1 + 2;
  range_pad = C0_pad * C1_pad * C1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  range_col = C0_pad * C1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  range_row = C0_pad * C1;
  for (k = 0; k < C1; k++) {
     k_pad = k + 1;
     k_col = k_pad * C0_pad;
     k_row = k_pad * C0;
     for (j = 0; j < C0; j++) {
        j_pad = j + 1;
        j_col = j_pad * C1_pad;
        j_row = j_pad * C1;
        for (i = 0; i < C1; i++) {
          i_pad = i + 1;
          i_col = i_pad * C1_pad;
          i_row = i_pad * C1;
          sum = ((long )0);
          idx_pad = k_pad * range_col + j_pad * C1_pad + i_pad;
          idx_col = k_col * range_col + j_col * C1 + i_col;
          idx_row = k_row * range_row + j_row * C1 + i_row;
          count = 0L;
          while (idx_col < (idx_col + 8L)) {
             while (idx_row < (idx_row + 8L)) {
                sum += orig[idx_pad] * orig[idx_row];
                idx_row ++;
                count ++;
             }
             idx_row = j_row;
             idx_pad ++;
             count += 6L;
          }
          sol[idx_pad] = sum / ((long )count);
          idx_col = i_col;
        }
     }
  }
}