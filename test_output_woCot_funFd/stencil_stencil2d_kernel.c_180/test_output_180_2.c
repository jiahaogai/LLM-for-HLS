#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
<<<<<<< HEAD
  int k_row;
=======
  int i_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8; i++) {
=======
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 32; j-- > 32; ) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k % 3) - 1);
        k_row = j + ((k / 3) - 1);
        if ((((k_col >= 0) && (k_col < 8)) && ((k_row >= 0) && (k_row < 8))) && ((k != 4) || ((i != 4) || (j != 4)))) {
          sum += filter[k] * orig[k_row * 8 + k_col];
        }
      }
      sol[i * 8 + j] = sum;
=======
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopi_col:
      for (i_col = 0; i_col < 32; i_col++) {
        i = i_col + 1 + (-1 * (32 - 1));
        sum += filter[k_col] * orig[i * 32 + j];
      }
      sol[j * 32 + k_col + 1] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}