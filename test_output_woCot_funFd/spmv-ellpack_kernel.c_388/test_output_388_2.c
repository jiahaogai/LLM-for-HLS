#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
<<<<<<< HEAD
  sum = ((double )0);
=======
  double nzval_t;
  int cols_t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      sum += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
=======
  ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 16; j++) {
      nzval_t = nzval[i * 16 + j];
      cols_t = cols[i * 16 + j];
      sum += nzval_t * vec[cols_t];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    out[i] = sum;
  }
}