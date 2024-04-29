Code: ### Generated Code:
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
  long idx;
  long idx_col;
  long idx_row;
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1; i <= 32; i++) {
     i_row = i + 15;
     i_col = i + 16;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
     for (j = 1; j <= 32; j++) {
        j_row = j + 15;
        j_col = j + 16;
        loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
        for (k = 1; k <= 32; k++) {
          k_row = k + 15;
          k_col = k + 16;
          idx_in = i_col + 32 * (j_col + 32 * k_col);
          t = orig[idx_in];
          idx_row = i_row + 32 * j_row;
          idx_col = i_col + 32 * j_col;
          loop_ko:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
          for (k = 1; k <= 32; k++) {
            idx = idx_col + 32 * k;
            sol[idx_row + 32 * k] = ((((k_col == 1) ? 1 : ((k_col == 2) ? 4 : ((k_col == 3) ? 7 : ((k_col == 4) ? 10 : 
              ((k_col == 5) ? 13 : ((k_col == 6) ? 16 : ((k_col == 7) ? 19 : ((k_col == 8) ? 22 : 
              ((k_col == 9) ? 25 : ((k_col == 10) ? 28 : ((k_col == 11) ? 31 : ((k_col == 12) ? 34 : 
              ((k_col == 13) ? 37 : ((k_col == 14) ? 41 : ((k_col == 15) ? 45 : ((k_col == 16) ? 49 : 
              ((k_col == 17) ? 54 : ((k_col == 18) ? 59 : ((k_col == 19) ? 64 : ((k_col == 20) ? 69 : 
              ((k_col == 21) ? 74 : ((k_col == 22) ? 79 : ((k_col == 23) ? 84 : ((k_col == 24) ? 90 : 
              ((k_col == 25) ? 96 : ((k_col == 26) ? 102 : ((k_col == 27) ? 108 : ((k_col == 28) ? 114 : 
              ((k_col == 29) ? 120 : ((k_col == 30) ? 126 : 132) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )