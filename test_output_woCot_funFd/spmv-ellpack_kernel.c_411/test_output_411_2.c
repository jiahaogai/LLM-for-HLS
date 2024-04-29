#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
<<<<<<< HEAD
  int index;
  int nz_index;
=======
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
<<<<<<< HEAD
  for (index = 0; index < 494; index++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (nz_index = cols[index]; nz_index < cols[index + 1]; nz_index++) {
      sum += nzval[nz_index] * vec[((int )nzval[nz_index]) - 1];
    }
    out[index] = sum;
=======
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}