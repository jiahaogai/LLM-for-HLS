#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int col;
  int flit;
=======
void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loop_row:
  for (row = 1; row < 64 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    for (col = 1; col < 64 - 1; col++) {
      tid = (row - 1) * 64 + col - 1;
      flit = 0;
      loop_filter:
      for (j = 0; j < 9; j++) {
        i = (row + ((0 + j) - 4)) * 64 + (col + ((0 + j) - 4));
        flit += filter[j] * orig[i];
      }
      sol[tid] = flit;
=======
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j <= 8192 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j + (-4 + k_col);
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk:
      for (k = 0; k < 9; k++) {
        i = i_col + (-4 + k);
        sum += filter[k] * orig[i];
      }
      sol[j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}