#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
<<<<<<< HEAD
  double nz;
=======
  double val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
<<<<<<< HEAD
    int_1:
    for (j = 0; j < 32; j++) {
      nz = nzval[i * 32 + j];
      vec[j] = nz;
      sum += nz * vec[j];
=======
    val = ((double )0);
    ints_1:
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum = sum + val * vec[cols[i * 32 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    out[i] = sum;
  }
}