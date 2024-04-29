#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
<<<<<<< HEAD
    for (j = 0; j < 16; j++) {
      sum += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
=======
    for (j = 0; j < 32; j++) {
      sum += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    out[i] = sum;
  }
}