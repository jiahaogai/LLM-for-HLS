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
  int k_col;
  int i_col;
<<<<<<< HEAD
  double sum;
=======
  int j_col;
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
=======
  outer:
  for (i = 0; i < 8192; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      i_col = 1 + k_col - 1;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopi:
      for (i = 1; i < 33 - 1; i++) {
        sum += ((double )(orig[i_col + ((i - 1) * 33)] * filter[k_col])) ;
      }
      sol[j] = sum;
      i_col = i_col + 33;
    }
    j = j + 33;
=======
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 1) * (k - 1) + i) + 1;
        i_col = ((8192 + 1) * (j - 1) + i) + 1;
        j_col = ((8192 + 1) * (k - 1) + j) + 1;
        t += filter[k] * orig[k_col] * orig[i_col] * orig[j_col];
      }
      sol[j] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}