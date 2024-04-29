#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[400][400],int sol[400][400],int filter[16][16])
{
  int row;
  int col;
  int row_up;
  int row_down;
  int col_left;
  int col_right;
  int flit_row;
  int flit_col;
  int sum;
=======
void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fl;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loop_row_up:
/* Standardize from: for(row = 1; row < 400 - 1; row++) {...} */
  row = 1;
  row_up = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_col_left:
/* Standardize from: for(col = 1; col < 400 - 1; col++) {...} */
  col = 1;
  col_left = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row_down:
/* Standardize from: for(row = 398; row > 0; row--) {...} */
  row = 398;
  row_down = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_col_right:
/* Standardize from: for(col = 398; col > 0; col--) {...} */
  col = 398;
  col_right = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_flit_row:
  flit_row = 8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_flit_col:
  flit_col = 8;
  
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
  sum = 0;
  loop_sum:
  for (row_up = -1; row_up <= 1; row_up++) {
     loop_sum_col:
     for (col_left = -1; col_left <= 1; col_left++) {
       sum += orig[row + row_up][col + col_left] * filter[flit_row + row_up][flit_col + col_left];
     }
  }
  sol[row][col] = sum;
=======
  outer:
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop:
      for (k = 0; k < 9; k++) {
        idx = i - 4 + ((k >> 6) & 3);
        idy = j - 4 + (k & 3);
        fl = filter[k];
        sol[i][j] += fl * orig[idx][idy];
      }
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}