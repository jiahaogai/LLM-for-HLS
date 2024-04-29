#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
/* Standardize from: for(row = 1;row < 8191;row++) {...} */
  for (row = 0; row <= 8191 - 1; row++) {
     row_up = row - 1;
     if (row_up == -1) {
       row_up = 8190;
     }
     row_down = row + 1;
     if (row_down == 8191) {
       row_down = 0;
     }
     loop_col:
/* Standardize from: for(col = 1;col < 8191;col++) {...} */
     for (col = 0; col <= 8191 - 1; col++) {
       col_up = col - 1;
       if (col_up == -1) {
         col_up = 8190;
       }
       col_down = col + 1;
       if (col_down == 8191) {
         col_down = 0;
       }
       t = 0;
       loop_flit:
/* Standardize from: for(flit = 0;flit < 9;flit++) {...} */
       for (flit = 0; flit <= 8; flit++) {
         i = row_up * 8191 + col_up;
         if (i == -1) {
           i = 0;
         }
         if (i == 8190 * 8191) {
           i = 8190 * 8191 - 1;
         }
         t += filter[flit] * orig[i];
         i = row * 8191 + col;
        if (i == -1) {
          i = 0;
        }
        if (i == 8190 * 8191) {
          i = 8190 * 8191 - 1;
        }
        orig[i] = sol[i];
        i = row_down * 8191 + col_down;
        if (i == -1) {
          i = 0;
        }
        if (i == 8190 * 8191) {
          i = 8190 * 8191 - 1;
        }
        sol[i] = t;
       }
     }
   }
}