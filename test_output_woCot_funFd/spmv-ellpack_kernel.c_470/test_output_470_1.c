#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
<<<<<<< HEAD
  for (i = 0; i < 49; i++) 
    out[i] = ((double )0);
=======
  double sum;
  double nz;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
  for (j = 0; j < 494; j++) {
    out[cols[j]] += nzval[j] * vec[j / 8];
=======
  spmv_1:
  for (i = 0; i < 49; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 5; j++) {
      nz = nzval[i * 5 + j];
      vec[j] = nz;
      sum += nz * vec[j];
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}