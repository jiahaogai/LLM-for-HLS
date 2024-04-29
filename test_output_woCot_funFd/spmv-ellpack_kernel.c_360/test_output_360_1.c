<<<<<<< HEAD
=======
For more information, see `ref_impl.c`.

>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
<<<<<<< HEAD
  double nzval_tmp;
  int cols_tmp;
=======
  double nz;
  double v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
<<<<<<< HEAD
  sum = ((double )0);
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    for (j = 0; j < 4; j++) {
      nzval_tmp = nzval[i * 4 + j];
      cols_tmp = cols[i * 4 + j];
      sum += nzval_tmp * vec[cols_tmp];
=======
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int tmp_begin = 0 + i * 16;
    int tmp_end = 16 + i * 16;
    spmv_2:
    for (j = tmp_begin; j < tmp_end; j++) {
      nz = nzval[j];
      v = vec[cols[j] - 1];
      sum += nz * v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    out[i] = sum;
  }
}