#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
<<<<<<< HEAD
  int nzidx;
  double sum;
=======
  int nnz;
  double sum;
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
<<<<<<< HEAD
  for (index = 0; index < 494; index++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (nzidx = cols[index]; nzidx < cols[index + 1]; nzidx++) {
      sum += nzval[nzidx] * vec[nzidx];
    }
    out[index] = sum;
=======
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    nnz = cols[i];
    index = nnz;
    loop_ellpack_2:
    while (index < 4940 && cols[index] == nnz) {
      sum += nzval[index] * vec[cols[index] - 1];
      index++;
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}