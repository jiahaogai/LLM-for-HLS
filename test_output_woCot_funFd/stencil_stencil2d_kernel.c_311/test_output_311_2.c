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
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
=======
  int k_col;
  int i_col;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loop_j:
/* Standardize from: for(j = 1;j < 8191;j++) {...} */
  for (j = 1; j < 8191; j++) {
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loop_k:
    for (k = 1; k < 8191; k++) {
      idx0 = k - 1;
      idx1 = k;
      idx2 = k + 1;
      idx3 = k + 1 + 8191;
      idx4 = k + 8191;
      idx5 = k - 1 + 8191;
      idx6 = idx1 - 8191;
      idx7 = idx1 + 1;
      idx8 = idx1 + 1 + 8191;
      idx = idx1 * 8192 + j;
      sol[idx] = ((filter[0] * orig[idx0]) + (filter[1] * orig[idx1]) + (filter[2] * orig[idx2]) + (filter[3] * orig[idx3]) + (filter[4] * orig[idx4]) + (filter[5] * orig[idx5]) + (filter[6] * orig[idx6]) + (filter[7] * orig[idx7]) + (filter[8] * orig[idx8])) / 408.0;
=======
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8192 - 1; i++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      loopk_col:
      for (k_col = 0; k_col < 9; k_col++) {
        i_col = i - 4 + k_col;
        sum += filter[k_col] * orig[i_col * 8192 + j];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}