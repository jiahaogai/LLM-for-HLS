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
  int t;
  int pt = 4 * 8192;
=======
  int k_col;
  int i_col;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[i + k * 8192];
      }
      sol[pt + i / 8 + (j / 8) * 128] = t;
=======
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = j - 4 + k_col;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loopk:
      for (k = 0; k < 5; k++) {
        i = i_col + k;
        sum += filter[k_col] * orig[i];
      }
      sol[j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}