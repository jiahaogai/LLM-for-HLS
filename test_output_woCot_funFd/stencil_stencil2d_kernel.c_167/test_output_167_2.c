#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int t;
=======
  int index;
  int fl;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
=======
  loop_j:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 1; j <= 32; j++) {
    int _in_j = 0 + 32 * (j - 1);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 8));
        i_col = ((k % 8) + 1);
        j_col = ((8 * j) + (i_col - 1));
        t += filter[k] * orig[((k_col * 256) + j_col)];
      }
      sol[((i * 256) + j)] = t;
=======
    loop_k:
/* Standardize from: for(k = 1;k < 33;k++) {...} */
    for (k = 1; k <= 32; k++) {
      int _in_k = 0 + 32 * (k - 1);
      int val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_fl:
/* Standardize from: for(fl = 0;fl < 9;fl++) {...} */
      for (fl = 0; fl < 9; fl++) {
        int _fl = fl;
        int _in_idx = _in_k + _fl;
        val += ((int )filter[_fl]) * orig[_in_idx];
      }
      sol[_in_j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}