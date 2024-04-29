#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
=======
  double sum;
  double val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  spmv_1:
  for (i = 0; i < 494; i++) {
<<<<<<< HEAD
    out[i] = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
=======
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum += val * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}