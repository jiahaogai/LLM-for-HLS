#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  double sum;
=======
  int sum;
  double FLT_SCALE = 1.0 / ((double )8192);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
<<<<<<< HEAD
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 0 + 1; j < 33 - 1; j++) {
=======
/* Standardize from: for(j = 1;j < 8;j++) {...} */
  for (j = 0 + 1; j < 8 + 1; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    loopk_col:
    for (k_col = 0; k_col < 32 + 1; k_col++) {
      i_col = k_col - 1;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk:
      for (k = 0; k < 3; k++) {
        i = i_col + k;
        sum += filter[k] * orig[i];
      }
      sol[j] = sum;
    }
    sol += 32;
    orig += 32;
=======
    loopk:
/* Standardize from: for(k = 1;k < 8;k++) {...} */
    for (k = 0 + 1; k < 8 + 1; k++) {
      i = k + ((j + 1) * 8);
      sum = ((filter[0] * orig[i]) + (filter[1] * (orig[i + 1] + orig[i - 1])) + (filter[2] * orig[i + 8]) + (filter[3] * (orig[i + 9] + orig[i - 9])) + (filter[4] * orig[i + 16]) + (filter[5] * (orig[i + 17] + orig[i - 17])) + (filter[6] * orig[i + 24]) + (filter[7] * (orig[i + 25] + orig[i - 25])) + (filter[8] * orig[i + 32]));
      sum *= FLT_SCALE;
      sol[i] = sum;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}