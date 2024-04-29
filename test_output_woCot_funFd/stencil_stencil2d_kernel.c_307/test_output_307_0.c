#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
<<<<<<< HEAD
  for (j = 1; j <= 8192 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
=======
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
<<<<<<< HEAD
      i_col = j + (-4 + k_col);
=======
      i_col = j - 4 + k_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk:
<<<<<<< HEAD
      for (k = 0; k < 9; k++) {
        i = i_col + k;
        sum += filter[k] * orig[i];
=======
      for (k = 0; k < 5; k++) {
        i = i_col + k;
        sum += filter[k_col] * orig[i];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[j] = sum;
    }
  }
}