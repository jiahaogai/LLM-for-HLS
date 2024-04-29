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
  
#pragma ACCEL PIPELINE auto{stencil_label1}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (8192 - 2 * 1)) * filter[0]) + ((8192 - 2 * 1) * (filter[1])) + ((8192 - 2 * 1) * (filter[2])) + ((8192 - 2 * 1) * (filter[3])) + ((8192 - 2 * 1) * (filter[4])) + ((8192 - 2 * 1) * (filter[5])) + ((8192 - 2 * 1) * (filter[6])) + ((8192 - 2 * 1) * (filter[7])) + ((8192 - 2 * 1) * (filter[8]));
      result -= ((8192 * (1 - 2 * 1)) * (orig[i - 1 + (8192 * (j - 1))])) + ((8192 - 2 * 1) * (1 - 2 * 1) * (orig[i + (8192 * (j - 1))])) + ((8192 - 2 * 1) * (orig[i + (8192 * (j + 1))])) + ((8192 * (1 - 2 * 1)) * (orig[i - 1 + (8192 * (j + 1))]));
      sol[i + (8192 * j)] = result;
=======
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{stencil_label2}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 8; k_col++) {
      sum = 0.0;
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 0 - 4 + 1; k_row <= 4 - 1; k_row++) {
        i = k_row + j;
        if ((((i >= 1) && (i <= 8192))) && (((k_col >= 1) && (k_col <= 8)))) {
          sum += filter[((k_row + 4) * 8) + k_col] * orig[i];
        }
      }
      sol[j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}