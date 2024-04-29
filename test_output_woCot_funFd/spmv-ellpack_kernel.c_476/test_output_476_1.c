#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
=======
  double sum;
  double nzval_tmp;
  int cols_tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
<<<<<<< HEAD
  for (j = 0; j < 9; j++) {
    i = cols[j];
    out[i] += nzval[j] * vec[j];
=======
  ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 9; j++) {
      nzval_tmp = nzval[i * 9 + j];
      cols_tmp = cols[i * 9 + j];
      sum += nzval_tmp * vec[cols_tmp];
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}