#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
=======
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1 + 0; j < 8192 + 1 - 1; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 1) * k) + i;
        i_col = ((8192 + 1) * k) + j;
        sum += filter[k] * orig[k_col] * orig[i_col];
=======
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j - 4 + k_col;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      loopk:
      for (k = 0; k < 5; k++) {
        i = i_col + k;
        sum += filter[k_col * 5 + k] * orig[i];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[j] = sum;
    }
  }
}