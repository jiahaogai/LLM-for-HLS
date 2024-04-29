#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[8192],int sol[8192],int filter[9])
=======
void stencil(double orig[8192],double sol[8192],double filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int k_col;
  int k_row;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 128; i++) {
=======
  loopj:
  for (j = 1; j < 64 - 1; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 64; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_index = (i + ((4 - 2) + (-7 + k))) * 64 + j + ((4 - 2) + (-7 + k));
        if (cur_index < 0) {
          cur_index = 0;
        }
        if (cur_index >= 8192) {
          cur_index = 8191;
        }
        result += cur_filter * orig[cur_index];
      }
      sol[i * 64 + j] = result;
=======
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      int orig_idx = 8192 * (j - 1) + (k_col - 4);
      double orig_val = orig[orig_idx];
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        int filter_idx = 9 * (k_row - 4) + (k_col - 4);
        double filter_val = filter[filter_idx];
        int sol_idx = 8192 * (j - 1) + (k_row - 1);
        sol[sol_idx] += orig_val * filter_val;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}